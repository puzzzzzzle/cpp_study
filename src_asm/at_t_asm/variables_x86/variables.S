.section .data                           #以下为数据段           
output:                     			#标签(变量名)：关联了当前地址
       .ascii "hello,world!\n"
len = . - output  			#定义字符串的长度, 直接被转换为了对应值
.section .text  					#以下为代码段
.globl _start						#起始的函数名
_start:
     movl $4, %eax       #系统调用值 $4—输出(write)   $4---立即数（常量）
     movl $1, %ebx      # I/O设备：0-标准输入  1-标准输出  2-错误输出
     movl $output,%ecx   #输出内容的地址
     movl $len,%edx   #输出内容的长度
     int $0x80   #Linux 0x080号系统调用
     
 	 movl $1,%eax       #系统调用值 $1—退出(exit)
     movl $0,%ebx       #退出码    可以用echo $? 查看
     int $0x80       #Linux系统调用