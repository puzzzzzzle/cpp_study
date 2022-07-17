//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/shared_ptr.hpp>

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

using namespace std;
// 玩家信息
class CPlayer {
  public:
  CPlayer(int id, string name, int fight, int gold)
      : id(id), name(name), fight(fight), gold(gold) {}
  void print() const {
    cout << "id:" << id << ", name:" << name << ", fight:" << fight
         << ", gold:" << gold << endl;
  }

  int id;       // 唯一id
  string name;  // 名字
  int fight;    // 战斗力
  int gold;     // 金币
};

// 要将类CPlayer中的某个属性字段设定为索引项，需定义与该属性字段同名的空的结构体
struct id {};
struct name {};
struct fight {};
struct gold {};
// BOOST_MULTI_INDEX_MEMBER宏 (创建表中的元素结构体名称, 索引的类型， 索引的名称 等于 tag<> 中设定的名称)

// 定义一个多索引容器类型
typedef multi_index_container
    <
        CPlayer, // 要将什么作为创建表的元素，传入该结构体名称
        indexed_by
        <
            ordered_unique<tag<id>,			BOOST_MULTI_INDEX_MEMBER(CPlayer, int, id)>,		// id为唯一索引，排序，与表项一一映射， tag<传入刚刚定义好的 struct id{} 对应的名称,类似数据库表的主键
            ordered_non_unique<tag<name>,	BOOST_MULTI_INDEX_MEMBER(CPlayer, string, name)>,	// name为不唯一索引，排序
            ordered_non_unique<tag<fight>,	BOOST_MULTI_INDEX_MEMBER(CPlayer, int, fight)>,		// fight为不唯一索引，排序
            ordered_non_unique<tag<gold>,	BOOST_MULTI_INDEX_MEMBER(CPlayer, int, gold)>		// gold为不唯一索引，排序
            >
        >player_table;


int main ()
{
  // 所有的玩家
  player_table allPlayer;
  allPlayer.insert(CPlayer(1, "zhao",90,1000));	// 赵
  allPlayer.insert(CPlayer(5, "qian",80,500));	// 钱
  allPlayer.insert(CPlayer(8,  "sun",100,800));	// 孙
  allPlayer.insert(CPlayer(4, "li",90,2500));		// 李
  allPlayer.insert(CPlayer(2, "zhou",20,1200));	// 周
  allPlayer.insert(CPlayer(3, "wu",60,1000));		// 吴
  allPlayer.insert(CPlayer(7, "zheng",40,700));	// 郑
  allPlayer.insert(CPlayer(6, "wang",100,800));	// 王

  ///			遍历
  // 使用get<index>方法得到玩家视图，其拷贝构造函数是被保护的，所以只能返回引用
  // 谨记：这里的index是定义容器时的顺序，而不是结构体中字段定义的顺序，从0开始，所以3对应的gold属性
  player_table::index<gold>::type& player_gold = allPlayer.get<3>();
  cout<<"以gold属性排序的结果"<<endl;
  player_table::index<gold>::type::iterator iter_gold = player_gold.begin();
  for(;iter_gold != player_gold.end();iter_gold++)
  {
    iter_gold->print();
  }
  cout<<"\n"<<endl;

  // 得到以id属性排序的玩家视图（视图与表的区别,视图仅仅是表的一个映像,在系统中并不为视图中的元素提供实际的存储空间,类似于对象实体和指向对象的指针）
  player_table::index<id>::type& player_ID = allPlayer.get<id>();
  cout<<"以id属性排序的结果"<<endl;
  player_table::index<id>::type::iterator iter_ID = player_ID.begin();
  for(;iter_ID != player_ID.end();iter_ID++)
  {
    iter_ID->print();
  }
  cout<<"\n"<<endl;

  // 得到以fight属性排序的玩家视图
  player_table::index<fight>::type& player_fight = allPlayer.get<fight>();
  cout<<"以fight属性排序的结果"<<endl;
  player_table::index<fight>::type::iterator iter_score = player_fight.begin();
  for (;iter_score!=player_fight.end();iter_score++)
  {
    iter_score->print();
  }
  cout<<"\n"<<endl;

  // 查找gold在[1000-2000]之间的玩家
  cout<<"查找gold在1000-2000之间的玩家"<<endl;
  player_table::index<gold>::type::iterator iter_low = allPlayer.get<gold>().lower_bound(1000);
  player_table::index<gold>::type::iterator iter_up = allPlayer.get<gold>().upper_bound(2000);
  while(iter_low != iter_up)
  {
    iter_low->print();
    iter_low++;
  }
  cout<<"\n"<<endl;

  ///			插入
  // insert() 函数返回std::pair<iterator,bool>对，成功时，iterator指向成功插入的对象，bool为true;失败时iterator指向之前已存在的对象，bool为false
  // 成功：
  bool bSuc = allPlayer.insert(CPlayer(9, "zheng",200,2000)).second;// 郑
  cout<<"插入成功结果值："<<bSuc<<endl;
  // 失败（因为ID为9的已存在）：
  bSuc = allPlayer.insert(CPlayer(9, "zheng2",300,1000)).second;// 郑2
  cout<<"插入失败结果值："<<bSuc<<endl;
  cout<<"\n"<<endl;

  ///			查找
  // 得到以name属性排序的玩家视图,并执行find()函数
  cout<<"查找zhou"<<endl;
  player_table::index<name>::type::iterator iter_name = allPlayer.get<name>().find("zhou");
  if (iter_name != allPlayer.get<name>().end())
  {
    cout<< "find zhou player!"<< endl ;
    iter_name->print();
  }
  else
  {
    cout<<"cant't find zhou player!"<< endl ;
  }

  ///			replace()修改
  player_table::index<name>::type& player_name = allPlayer.get<name>();
  // 成功的replace()
  player_table::index<name>::type::iterator iter_wang = player_name.find("wang"); // 查找wang
  if (iter_wang != player_name.end())
  {
    cout<<"找到wang，结果如下"<<endl;
    iter_wang->print();

    CPlayer wang = *iter_wang;
    wang.gold = 1000;
    wang.id = 66;	  // 由于id是唯一的，但66不存在，修改后replace会返回成功
    bSuc = player_name.replace(iter_wang,wang);
    cout<<"修改wang的id为66的结果值："<<bSuc<<endl;
  }
  // 失败的replace()
  iter_wang = player_name.find("wang"); // 重新查找wang
  if (iter_wang != player_name.end())
  {
    cout<<"重新找到wang，结果如下"<<endl;
    iter_wang->print();

    CPlayer wang = *iter_wang;
    wang.gold = 1000;
    wang.id = 1;	  // 由于id是唯一的，但1已存在，修改后replace会返回失败，此时replace可以保证容器不会发生任何变化
    bSuc = player_name.replace(iter_wang,wang);
    cout<<"修改wang的id为1的结果值："<<bSuc<<endl;
  }
  // 注意：replace()会发生两次赋值拷贝，如果结构很大并且使用的很频繁，有可能会成为性能瓶颈
  cout<<"\n"<<endl;

  ///			modify()修改
  // 先定义修改的函数对象，这里以修改id为例
  class CModifyPlayer
  {
public:
    CModifyPlayer(int id):m_id(id)
    {
    }
    void operator()(CPlayer& player)
    {
      player.id = m_id;
    }
private:
    int m_id;
  };

  // 成功的modify()
  player_table::index<name>::type::iterator iter_zheng = player_name.find("zheng"); // 查找zheng
  if (iter_zheng != player_name.end())
  {
    cout<<"找到zheng，结果如下"<<endl;
    iter_zheng->print();

    // 由于id是唯一的，但50不存在，修改后modify会返回成功
    bSuc = player_name.modify(iter_zheng,CModifyPlayer(50));
    cout<<"修改zheng的id为50的结果值："<<bSuc<<endl;
  }

  cout<<"遍历以name排序的视图"<<endl;
  iter_name = player_name.begin();
  for(;iter_name != player_name.end();iter_name++)
  {
    iter_name->print();
  }

  // 失败的modify()
  iter_zheng = player_name.find("zheng"); // 重新查找zheng
  if (iter_zheng != player_name.end())
  {
    cout<<"重新找到zheng，结果如下"<<endl;
    iter_zheng->print();

    // 由于id是唯一的，但5已经存在，修改后modify会返回失败，且本元素（iter_zheng）也会被删掉！！！！
    bSuc = player_name.modify(iter_zheng,CModifyPlayer(5));
    cout<<"修改zheng的id为5的结果值："<<bSuc<<endl;
  }

  cout<<"再次遍历以name排序的视图"<<endl;
  iter_name = player_name.begin();
  for(;iter_name != player_name.end();iter_name++)
  {
    iter_name->print();
  }
  cout<<"\n"<<endl;

  ///			删除
  cout<<"删除id为2的玩家"<<endl;
  player_table::index<id>::type::iterator iter_2 = player_ID.find(2);
  if (iter_2 != player_ID.end())
  {
    player_ID.erase(iter_2);
  }
  cout<<"再次遍历以id排序的视图"<<endl;
  iter_ID = player_ID.begin();
  for(;iter_ID != player_ID.end();iter_ID++)
  {
    iter_ID->print();
  }
  cout<<"\n"<<endl;

  getchar();
  return 0 ;
}
int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}