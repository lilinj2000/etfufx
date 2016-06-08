#include "TraderUFX.hh"

#include <iostream>

void TestTrader()
{
  etf::TraderRequest* lp_TraderRequest = new etf::TraderRequest();
  if(lp_TraderRequest->InitConn("demo", "license.dat", "172.16.90.16:9003") != 0)
  {
    return;
  }

  char exch_type[32];
  char contract_code[32];
  char second_code[32];
  char arbitrage_code[32];
  int l_entrust_no;
  char c_bs;
  char c_direction; 
  char c_hedge; 
  int l_entrust_amount;
  double en_entrust_price;

  std::cout<<"------------------------------------------------"<<std::endl;
  std::cout<<" [1]  331100 login                           "<<std::endl;
  // std::cout<<" [2]  331102 logout                           "<<std::endl;
  std::cout<<" [0]  Exit                                      "<<std::endl;
  std::cout<<"------------------------------------------------"<<std::endl;

  while(1)
  {
    int cmd;  
    std::cin>>cmd;
    switch(cmd){
      case 1:
        //lp_TraderRequestMode->ReqFunction331100("101300864", "888888", '7');//101300316 | 123456
        //lp_TraderRequestMode->ReqFunction331100("879366", "123456", '7');
        lp_TraderRequest->ReqFunction331100("10002", "123456", '7');
        break;
        
      // case 2:
      //   lp_TraderRequestMode->ReqFunction331102();
      //   break;
      // case 3:
      //   lp_TraderRequestMode->ReqFunction331150();
      //   break;
      // case 4:
      //   {
      //     cerr<<" exch_type > "; cin>>exch_type; 
      //     cerr<<" contract_code > "; cin>>contract_code; 
      //     lp_TraderRequestMode->ReqFunction330850(exch_type, contract_code);
      //   }
      //   break;
      // case 5:
      //   {
      //     //cerr<<" exch_type > "; cin>>exch_type; 
      //     //cerr<<" contract_code > "; cin>>contract_code; 
      //     lp_TraderRequestMode->ReqFunction330851("", "", "");
      //   }
      //   break;
      // case 6:
      //   lp_TraderRequestMode->ReqFunction330852();
      //   break;
      // case 7:
      //   lp_TraderRequestMode->ReqFunction331850();
      //   break;
      // case 8:
      //   lp_TraderRequestMode->ReqFunction331851();
      //   break;
      // case 9:
      //   lp_TraderRequestMode->ReqFunction332213();
      //   break;
      // case 10:
      //   {
      //     cerr<<" exch_type > "; cin>>exch_type; 
      //     cerr<<" contract_code > "; cin>>contract_code; 
      //     lp_TraderRequestMode->ReqFunction338200(exch_type, contract_code);
      //   }
      //   break;
      // case 11:
      //   {
      //     cerr<<" exch_type > "; cin>>exch_type; 
      //     cerr<<" contract_code > "; cin>>contract_code; 
      //     cerr<<" c_bs > "; cin>>c_bs; 
      //     cerr<<" c_direction > "; cin>>c_direction; 
      //     cerr<<" c_hedge > "; cin>>c_hedge; 
      //     cerr<<" en_entrust_price > "; cin>>en_entrust_price; 
      //     lp_TraderRequestMode->ReqFunction338201(exch_type, contract_code, c_bs, c_direction, c_hedge, en_entrust_price);
      //   }
      //   break;
      // case 12:
      //   {
      //     //cerr<<" exch_type > "; cin>>exch_type; 
      //     //cerr<<" contract_code > "; cin>>contract_code; 
      //     //cerr<<" c_bs > "; cin>>c_bs; 
      //     //cerr<<" c_direction > "; cin>>c_direction; 
      //     //cerr<<" c_hedge > "; cin>>c_hedge; 
      //     //cerr<<" l_entrust_amount > "; cin>>l_entrust_amount; 
      //     //cerr<<" en_entrust_price > "; cin>>en_entrust_price; 
      //     //lp_TraderRequestMode->ReqFunction338202(exch_type, contract_code, c_bs, c_direction, c_hedge, l_entrust_amount, en_entrust_price);
      //     lp_TraderRequestMode->ReqFunction338202("F4", "IF1409", '1', '1', '0', 1, 2300);
      //   }
      //   break;
      // case 13:
      //   {
      //     cerr<<" exch_type > "; cin>>exch_type; 
      //     cerr<<" contract_code > "; cin>>contract_code; 
      //     cerr<<" second_code > "; cin>>second_code; 
      //     cerr<<" arbitrage_code > "; cin>>arbitrage_code; 
      //     cerr<<" c_bs > "; cin>>c_bs; 
      //     cerr<<" c_direction > "; cin>>c_direction; 
      //     lp_TraderRequestMode->ReqFunction338203(exch_type, contract_code, second_code, arbitrage_code, c_bs, c_direction);
      //   }
      //   break;
      // case 14:
      //   {
      //     //cerr<<" exch_type > "; cin>>exch_type; 
      //     cerr<<" l_entrust_no > "; cin>>l_entrust_no; 
      //     lp_TraderRequestMode->ReqFunction338217("F4", l_entrust_no, "438");
      //   }
      //   break;
      // case 15:
      //   lp_TraderRequestMode->ReqFunction338300();
      //   break;
      // case 16:
      //   lp_TraderRequestMode->ReqFunction338301();
      //   break;
      // case 17:
      //   lp_TraderRequestMode->ReqFunction338302("");
      //   break; 
      // case 18:
      //   lp_TraderRequestMode->ReqFunction338303();
      //   break; 
      // case 19:
      //   lp_TraderRequestMode->ReqFunction338307();
      //   break;
      // case 20:
      //   //cerr<<" en_entrust_price > "; cin>>en_entrust_price; 
      //   lp_TraderRequestMode->ReqFunction338204(2300);
      //   break;
      // case 21:
      //   lp_TraderRequestMode->ReqFunction338400();
      //   break;
      // case 22:
      //   lp_TraderRequestMode->ReqFunction338401();
      //   break;
      // case 23:
      //   lp_TraderRequestMode->ReqFunction338402();
      //   break;
      // case 24:
      //   lp_TraderRequestMode->ReqFunction338403();
      //   break;
      // case 25:
      //   lp_TraderRequestMode->ReqFunction338304();
      //   break;
      // case 30:
      //   lp_TraderRequestMode->ReqFunction338313();
      //   break;
      case 0:
        exit(0);
    }
  }
  
  delete(lp_TraderRequest);

  return;
}

int main()
{
  std::cout<<"-----------------------------------------------"<<std::endl;
  std::cout<<" [1] TestTrader                                "<<std::endl;
  // std::cout<<" [2] TestMD                                    "<<std::endl;
  std::cout<<" [0] Exit                                      "<<std::endl;
  std::cout<<"-----------------------------------------------"<<std::endl;

  while(1)
  {
    int cmd;  
    std::cin>>cmd;
    switch(cmd){
      case 1: 
        TestTrader();
        break;
        
      // case 2:
      //   TestMD();
      //   break;
        
      case 0:
        exit(0);
    }
  }

  getchar();

  return 0;
}
