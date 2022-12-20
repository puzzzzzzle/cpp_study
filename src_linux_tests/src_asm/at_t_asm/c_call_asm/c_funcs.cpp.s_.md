## 
### 空函数
```c
void void_ret_func() { return; }
```
```asm
void_ret_func:
	pushq	%rbp
	movq	%rsp, %rbp
	nop
	popq	%rbp
	ret
```
### 返回int, 栈上分配一个数据
```c
int ret_int_func() {
  int i = 42;
  return i;
}
```
```asm
ret_int_func:
	pushq	%rbp
	movq	%rsp, %rbp
	
	movl	$42, -4(%rbp) # 直接向rbp 指针向下4 的位置写入数值, 没有挪动rsp , 目测是因为这个函数是叶子函数, 不需要
	movl	-4(%rbp), %eax  # 写入返回值
	
	popq	%rbp    # 没有挪动rsp, 随意不需要     movq %rbp, %rsp
	ret
```

### 传入int
```c
void int_arg_func(int arg) {}
```
```asm
int_arg_func:
	pushq	%rbp
	movq	%rsp, %rbp
	
	// 从di寄存器获取参数, 放到栈上, 所以对于c传参不用栈而用寄存机加速的优化优化了个寂寞? 刚进函数就要全部在栈上保存一遍?
	// int 只有4个字节, 使用edi就行, 不用rdi
	movl	%edi, -4(%rbp) 
	
	popq	%rbp
	ret
```

### 返回 小的结构体
```c
SmallStruct return_SmallStruct() {
  SmallStruct data{};
  return data;
}
```
```asm
return_SmallStruct:
	pushq	%rbp
	movq	%rsp, %rbp
	
	// 分配栈空间
	// 这里和面的叶子函数不一样
	// 前面只是用栈空间, 没有改rsp
	// 这里同时改了rsp指针
	// 因为 struct 的构造, 在c++中也是要调用构造函数的, 这也是一次隐式的函数调用
	// 这会导致当前函数不是叶子函数
	subq	$16, %rsp  

	// 初始化栈变量为0
	movl	$0, -16(%rbp)
	
	// 计算栈上的结构体的地址, 放在 rax 中
	leaq	-16(%rbp), %rax
	
	// 准备调用构造函数的参数
	// 在汇编中, 没有所谓的对象
	// 构造函数只是一个第一个参数以结构体指针的普通函数
	// 根据调用规则, 第一个参数放在rdi上
	movq	%rax, %rdi
	// 本地没有什么药保存的寄存器, 直接调用构造函数
	// call 相当于 pushq %rip; jmp _ZN11SmallStructC1Ev
	// 当然, 这其中还有 FAR Near 跳转, 不同的寻址方式等隐藏在底层了, 这里只是一个简化
	// 待定 :  far 时 同时修改 CS IP, 我记得再64位下 CS 默认一直填0了
	// 压栈下一条指令, 然后强制跳转
	call	_ZN11SmallStructC1Ev
	
	// 准备返回值
	// 对于较小的对象, 直接放在 rax中返回
	movl	-16(%rbp), %eax
	// leave 相当于    movq %rbp, %rsp;  popq %rbp;
	// 先恢复 rsp 寄存器 为分配栈 前的状态, 然后恢复rbp寄存器
	// 非叶子函数由于修改过rsp, 所以需要恢复
	leave
	// 返回 相当于 popq %rip
	// 待定 :  far 时 同时修改 CS IP, 我记得再64位下 CS 默认一直填0了
	ret
```
### 返回大结构体
1. 对于在函数中声明一个结构体, 初始化后直接返回的, 现代编译器可以做到0次拷贝, 放心的用
1. 对于如下代码:
```
OperatorLogClass get_obj()
{
  OperatorLogClass obj{};
  return obj;
}
int main(int argc, char **argv) {
  auto obj = get_obj();
  return 0;
}
```
1. 在现代编译器下会优化为(伪代码, 有些只能用汇编实现):
```
OperatorLogClass * get_obj(OperatorLogClass * inObj)
{
  memset(inObj,sizeof(OperatorLogClass0,0)  // 初始化内存
  OperatorLogClass::OperatorLogClass(inObj)  // 调用构造函数
  return inObj;
}
int main(int argc, char **argv)
{
  OperatorLogClass obj; // 不做任何初始化, 栈内存只是分配, 给下面的函数初始化
  get_obj(&obj);
}
```
```asm
return_BigStruct:
	pushq	%rbp
	movq	%rsp, %rbp
	
	// 分配栈
	// 注意, 在这个栈上并没有直接分配结构体, 而是直接使用调用方传入的地址
	// 编译器在这里优化掉了栈上的分配
	subq	$16, %rsp
	
	// 返回的大结构体是通过在上层调用函数栈上分配空间, 向下传入地址实现的
	// 保存返回结构体的地址
	movq	%rdi, -8(%rbp)
	
	// 把 返回结构体 地址存储在 rsi 中
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	
	// 初始化数据为0
	movl	$0, %eax
	movl	$10, %edx
	movq	%rsi, %rdi // 把返回结构体地址存储在rdi中
	movq	%rdx, %rcx
	// rep 重复当前指令, 次数为rcx指定的次数, 当前为 $10, %edx 10次 , 共 8*10 = 80 byte
	// stos 将eax寄存器(当前为0) 传送到 rdi 指定的内存中, 即: 返回值所在的地址处
	// 这样就完成了将目标结构体所有值置为0的操作
	rep stosq
	
	// 调用构造函数
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN9BigStructC1Ev
	
	nop
	// 写入返回值, 这里返回了上层栈给到的地址
	movq	-8(%rbp), %rax
	leave
	ret
```
#### 调用返回大结构体的函数
```c++
void test_func()
{
  auto obj =  return_BigStruct();
}
```
```asm
test_func:
	pushq	%rbp
	movq	%rsp, %rbp
	
	// 在父栈上申请空间
	subq	$80, %rsp

    // 把父栈上的地址作为参数传入
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	// 调用函数
	call	return_BigStruct

	leave
	ret
```

### 大结构体作为参数拷贝输入
1. 其实是在调用方分配了两份数据, 一份作为参数传入
```c++
void input_BigStruct_1(BigStruct st) {
  st.value_1 = 1;
}
void test_func_1()
{
  BigStruct obj{};
  input_BigStruct_1(obj);
}
```
```asm
input_BigStruct_1:
	pushq	%rbp
	movq	%rsp, %rbp
	
	// rbp 向上就是参数
	movq	$1, 16(%rbp)
	
	popq	%rbp
	ret
	
test_func_1:
	pushq	%rbp
	movq	%rsp, %rbp
	// 分配栈空间
	subq	$160, %rsp


    // 初始化第一份数据
	leaq	-80(%rbp), %rsi
	movl	$0, %eax
	movl	$10, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN9BigStructC1Ev

    // 复制第二份数据
	movq	-80(%rbp), %rax
	movq	%rax, (%rsp)
	movq	-72(%rbp), %rax
	movq	%rax, 8(%rsp)
	movq	-64(%rbp), %rax
	movq	%rax, 16(%rsp)
	movq	-56(%rbp), %rax
	movq	%rax, 24(%rsp)
	movq	-48(%rbp), %rax
	movq	%rax, 32(%rsp)
	movq	-40(%rbp), %rax
	movq	%rax, 40(%rsp)
	movq	-32(%rbp), %rax
	movq	%rax, 48(%rsp)
	movq	-24(%rbp), %rax
	movq	%rax, 56(%rsp)
	movq	-16(%rbp), %rax
	movq	%rax, 64(%rsp)
	movq	-8(%rbp), %rax
	movq	%rax, 72(%rsp)
	
	// 直接调用, 即: 参数放在栈上传入了, 上面那份复制的直接用于参数
	call	input_BigStruct_1

	leave
	ret
```