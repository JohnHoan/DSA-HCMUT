#include "processData.h"

enum CodeValue
{
	sdCode,
	cdCode,
	slCode,
	insCode,
	delCode,
	updCode,
	obCode,
	cbCode,
	osCode,
	csCode
};

static map<string, CodeValue> s_mapCodeValues = {
	{"SD", sdCode},
	{"CD", cdCode},
	{"SL", slCode},
	{"INS", insCode},
	{"DEL", delCode},
	{"UPD", updCode},
	{"OB", obCode},
	{"CB", cbCode},
	{"OS", osCode},
	{"CS", csCode}};





ProcessData::ProcessData()
{
  data=new CurrencyList();
}
ProcessData::~ProcessData()
{
}
/* 
	Split the command line into instruction and its parameters
	(This version is simplified to return just the instruction only; students should rewrite to make it return instruction's parameters)
	Input:
		line: the command line
		sp: pass-by-reference parameter used as an output: return the array of strings keeping instruction and its parameter
	Output: return the number of elements in array sp.	
*/
int ProcessData::split(string line, string *&sp)
{
	sp = new string[MAXSIZECODE];
	const string SEP = " ";
	int pos=0, lastpos = 0, idx = 0;
  while(unsigned(pos)<unsigned(line.length())){
    pos = line.find(SEP, lastpos);
	  sp[idx] = line.substr(lastpos, pos - lastpos);
	  idx++;
    lastpos=pos+1;
  }
	return idx;
}

int ProcessData::process(string line)
{
	string *p;
	int n = ProcessData::split(line, p);
	if (n <= 0)
	{
		delete[] p;
		return -1;
	}
	int res = -1;
	try
	{
		switch (s_mapCodeValues[p[0]])
		{
		case insCode:
			res = this->insert(p, n);
			break;
		case updCode:
			res=this->update(p, n);
      break;
		case delCode:
			res=this->remove(p, n);
      break;
    case sdCode:
			res=this->sdFuction(p, n);
      break;
    case cdCode:
			res=this->cdFuction(p, n);
      break;
    case slCode:
			res=this->slFuction(p, n);
      break;
    case obCode:
			res=this->obFuction(p, n);
      break;
    case osCode:
			res=this->osFuction(p, n);
      break;
    case cbCode:
			res=this->cbFuction(p, n);
      break;
    case csCode:
			res=this->csFuction(p, n);
      break;
		default:
			res = -1;
		}
	}
	catch (invalid_argument iax)
	{
		delete[] p;
		return res;
	}
	delete[] p;
	return res;
}
/*
	To process insert instruction
	(This is the simplified version)
	Input:
		sp: pointer to string array keeping instruction and its parameters
		n: the number of elements in sp
	Output:
		return the result as required
*/
int ProcessData::insert(const string *sp, const int n)
{
  if(n>6) return -1;
  CurrencyData currency;
  currency.BC=sp[1];
  currency.QC=sp[2];
  ExchangeRate value;
  value.time=sp[3];
  value.BP=sp[4];
  value.AP=sp[5];
  int idx;
  if(data->find(currency.BC,currency.QC,idx)){
    CurrencyNode* currItem=this->data->getHead();
    while(idx!=0){
      currItem=currItem->link;
      idx--;
    }
    currItem->currency_data.AVLTree->insert(value);
    return currItem->currency_data.AVLTree->getRootData();
  }
  else{
    currency.AVLTree->insert(value);
    data->insert_currency(currency);
    return currency.AVLTree->getRootData();
  }
}
int ProcessData::update(const string *sp, const int n){
  if(n>5||n<0) return -1;
  CurrencyData currency;
  currency.BC=sp[1];
  currency.QC=sp[2];
  int idx;
  if(data->find(currency.BC,currency.QC,idx)){
    CurrencyNode* currItem=this->data->getHead();
    while(idx!=0){
      currItem=currItem->link;
      idx--;
    }
    Node_Exrate* tmp;
    tmp=currItem->currency_data.AVLTree->search(sp[3]);
    if(tmp!=NULL){
      tmp->data.BP=sp[4];
      tmp->data.AP=sp[5];
      return currency.AVLTree->getRootData();
    }
    return 0;
  }
  return 0;
}

int ProcessData::remove(const string *sp, const int n){
  CurrencyData currency;
  currency.BC=sp[1];
  currency.QC=sp[2];
  int idx;
  if(data->find(currency.BC,currency.QC,idx)){
    CurrencyNode* currItem=this->data->getHead();
    while(idx!=0){
      currItem=currItem->link;
      idx--;
    }
    if(n==3){
      currItem->currency_data.AVLTree->clear();
      return -1;
    }else if(n==4){
      currItem->currency_data.AVLTree->remove(sp[3]);
      return currItem->currency_data.AVLTree->getRootData();
    }else if(n==5){
      string time1=sp[3];
      string time2=sp[4];
      if(stoi(time1)-stoi(time2)>=0) return -1;
      currItem->currency_data.AVLTree->findTime(time1,time2);
      int size=currItem->currency_data.AVLTree->myTime.size();
      if(size==currItem->currency_data.AVLTree->getCount()){
        currItem->currency_data.AVLTree->clear();
        return -1;
      }
      for(int i=0;i<size;i++){
        currItem->currency_data.AVLTree->remove(currItem->currency_data.AVLTree->myTime.at(i));
      }
      return currItem->currency_data.AVLTree->getRootData();
    }else 
      return -1;
  }
  return -1;

}

int ProcessData::sdFuction(const string *sp, const int n){
  if(n>2) return -1;
  string tmp=getMoney();
  if(tmp==""){
    setMoney(sp[1]);
    return 1;
  }
  return -1;
}
int ProcessData::cdFuction(const string *sp, const int n){
  if(n>1) return -1;
  string result=getMoney();
  if(result!="")
    return stoi(result);
  return -1;
} 
int ProcessData::slFuction(const string *sp, const int n){
  if(n>2) return -1;
  string tmp=getMoney();
  if(tmp==""){
    return -1;
  }
  setLeverage(sp[1]);
  return stoi(tmp)*(stoi(sp[1]));
}
int ProcessData::obFuction(const string *sp, const int n){
  if(n>6||n<0) return -1;
  if(sp[1]!="USD"&&sp[2]!="USD") return -1;
  mapID.insert(pair<string,string>(sp[5],sp[3]));
  string pass=sp[1]+" "+sp[2]+" "+sp[3]+" "+sp[4];
  myMapPairCurrency.insert(pair<string,string>(sp[5],pass));
  CurrencyData currency;
  currency.BC=sp[1];
  currency.QC=sp[2];
  int idx;
  if(data->find(currency.BC,currency.QC,idx)){
    CurrencyNode* currItem=this->data->getHead();
    while(idx!=0){
      currItem=currItem->link;
      idx--;
    }
    Node_Exrate* tmp;
    tmp=currItem->currency_data.AVLTree->search(sp[3]);
    if(tmp!=NULL){
      float lot=stof(sp[4])*100000;
      float AP=stof(tmp->data.AP);
      float result=AP*lot;
      return ceil(result);
    }
    return -1;
  }
  return -1;
}
int ProcessData::osFuction(const string *sp, const int n){
  if(n>6||n<0) return -1;
  if(sp[1]!="USD"&&sp[2]!="USD") return -1;
  mapID.insert(pair<string,string>(sp[5],sp[3]));
  string pass=sp[1]+" "+sp[2]+" "+sp[3]+" "+sp[4];
  myMapPairCurrency.insert(pair<string,string>(sp[5],pass));
  CurrencyData currency;
  currency.BC=sp[1];
  currency.QC=sp[2];
  int idx;
  if(data->find(currency.BC,currency.QC,idx)){
    CurrencyNode* currItem=this->data->getHead();
    while(idx!=0){
      currItem=currItem->link;
      idx--;
    }
    Node_Exrate* tmp;
    tmp=currItem->currency_data.AVLTree->search(sp[3]);
    if(tmp!=NULL){
      float lot=stof(sp[4])*100000;
      float BP=stof(tmp->data.BP);
      float result=BP*lot;
      return ceil(result);
    }
    return -1;
  }
  return -1;
}
int ProcessData::cbFuction(const string *sp, const int n){
  if(n>3||n<0) return -1;
  if(stoi(getMoney())<=0) return -1;
  map<string,string>::iterator myMap;
  myMap=mapID.find(sp[2]);
  if(myMap!=mapID.end()){
    mapID.erase(myMap);
    if(myMapPairCurrency.size()==0) return -1;
    map<string,string>::iterator it;
    it=myMapPairCurrency.find(sp[2]);
    if(it!=myMapPairCurrency.end()){
      string passOS=myMapPairCurrency.at(sp[2]);
      string *p;
      int n=ProcessData::split(passOS,p);
      if(n>4) return -1;
      string BC=p[0];
      string QC=p[1];
      string time1=p[2];
      string lot=p[3]; 
      int idx;
      if(data->find(BC,QC,idx)){
        CurrencyNode* currItem=this->data->getHead();
        while(idx!=0){
          currItem=currItem->link;
          idx--;
        }
        string timeInput=sp[1];
        string maxTime=currItem->currency_data.AVLTree->findMaxTime(timeInput);
        Node_Exrate* tmp;
        tmp=currItem->currency_data.AVLTree->search(maxTime);
        if(tmp!=NULL){
          string u2=tmp->data.AP;
          Node_Exrate* tmp1;
          tmp1=currItem->currency_data.AVLTree->search(time1);
          string u1=tmp1->data.BP;
          float result=(stof(u1)-stof(u2))*stof(lot)*100000;
          float money1;
          if(QC!="USD"){
            money1=stof(getMoney())+(result/stof(tmp->data.AP));
          }
          else{
            money1=stof(getMoney())+result;
          }
          this->setMoney(to_string(floor(money1)));
          if(result<0) return floor(result);
          return ceil(result);
        }
        return -1;    
      }else{
        return -1;
      }      
    }
    return -1; 
  }
  return -1;
}
int ProcessData::csFuction(const string *sp, const int n){
  if(n>3||n<0) return -1;
  if(stoi(getMoney())<=0) return -1;
  map<string,string>::iterator myMap;
  myMap=mapID.find(sp[2]);
  if(myMap!=mapID.end()){
    mapID.erase(myMap);
    if(myMapPairCurrency.size()==0) return -1;
    map<string,string>::iterator it;
    it=myMapPairCurrency.find(sp[2]);
    if(it!=myMapPairCurrency.end()){
      string passOS=myMapPairCurrency.at(sp[2]);
      string *p;
      int n=ProcessData::split(passOS,p);
      if(n>4) return -1;
      string BC=p[0];
      string QC=p[1];
      string time1=p[2];
      string lot=p[3];
      int idx;
      if(data->find(BC,QC,idx)){
        CurrencyNode* currItem=this->data->getHead();
        while(idx!=0){
          currItem=currItem->link;
          idx--;
        }
        string timeInput=sp[1];
        string maxTime=currItem->currency_data.AVLTree->findMaxTime(timeInput);
        Node_Exrate* tmp;
        tmp=currItem->currency_data.AVLTree->search(maxTime);
        if(tmp!=NULL){
          string u2=tmp->data.BP;
          Node_Exrate* tmp1;
          tmp1=currItem->currency_data.AVLTree->search(time1);
          string u1=tmp1->data.AP;
          float result=(stof(u2)-stof(u1))*stof(lot)*100000;
          float money1;
          if(QC!="USD"){
            money1=stof(getMoney())+(result/stof(tmp->data.AP));
          }
          else{
            money1=stof(getMoney())+result;
          }
          this->setMoney(to_string(floor(money1)));
          if(result<0) return floor(result);
          return ceil(result);
        }
        return -1;     
      }else{
        return -1;
      }      
    }
    return -1;
  }  
  return -1;
}


