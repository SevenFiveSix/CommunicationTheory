#include<bits/stdc++.h>

using namespace std;

const double eps = 1e-6;

//定义结构体，当前编码范围
struct Range{
double low;
double high;
};
 
//构造范围函数
Range CreateRange(double x,double y)
{
  Range r;
  r.high = y;
  r.low = x;
  return r;
}


int main()  {
  int size;
  map<char,Range> imap;
  double x,y;
  char buf; 
  double low(0),high(1),range(1),pu(1);

  //字符概率分布存储文件
  ifstream fin_s("codeRule.txt",ios::in);
  if(!fin_s)  {
    cout<<"open file error! file name need to be \"codeRule.txt\""<<endl;
  }
  fin_s >> size;
  if(size > 0)  {
    for(int iter = 0;iter < size; iter++) {
      fin_s >> buf >> x >> y;
      imap[buf] = CreateRange(x,y);
    }
  }
  fin_s.close();

  //待编码字符串存储文件
  ifstream fin("toBeCode.txt",ios::in);
  if(!fin)  {
    cout <<"open file error! file name need to be \"toBeCode.txt\"" << endl;
    return -1;
  }

  while(fin >> buf && !fin.eof()) {
    high = low + range * imap[buf].high ;
    low = low + range * imap[buf].low ;
    range = high - low;
    pu *= imap[buf].high - imap[buf].low;
    cout << buf << endl;
    cout<<"low:"<<low<<" high:"<<high<<endl;
  }
  fin.close();

  double codecRes = low;

  /*******codec*******/
  //F(n)即变量low
  int codeLength = -log2(pu);
  int pos = 0;
  cout << "codeLength: " << codeLength << endl;
  cout << "code: ";
  for(int iter = 0; iter < codeLength ; iter++) {
    low *= 2;
    if(low >= 1) {
      low -= 1;
      cout << 1;
    } else cout << 0;
  }
  cout << endl;

  /*******decodec*******/
  string decodecRes = "";
  while(codecRes != 0) {
    for(map<char , Range>::iterator iter = imap.begin() ; iter != imap.end() ; iter++) {
      if(codecRes < iter->second.high) {
        codecRes -= iter->second.low;
        codecRes /= (iter->second.high - iter->second.low);
        decodecRes += iter->first;
        break;
      }
    }
  }
  //缺位检查
  double pu_decodec = 1 / pow(2, codeLength);
  for(int iter = 0 ; iter < decodecRes.size() ; iter++) {
    pu_decodec /= (imap[decodecRes[iter]].high - imap[decodecRes[iter]].low);
  }
  while(pu_decodec != 1) {
    decodecRes += imap.begin()->first;
    pu_decodec /= (imap.begin()->second.high - imap.begin()->second.low);
  }
  cout << endl << "decode: " << decodecRes << endl;

  return 0; 
}