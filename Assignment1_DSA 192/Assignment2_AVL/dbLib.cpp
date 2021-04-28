#include "dbLib.h"
Node_Exrate* AVL::rotateRight(Node_Exrate *&node){
	Node_Exrate* tmp=node->left;
  node->left=tmp->right;
  tmp->right=node;
  node=tmp;
  return node;
}
Node_Exrate* AVL::rotateLeft(Node_Exrate *&node){
	Node_Exrate* tmp=node->right;
  node->right=tmp->left;
  tmp->left=node;
  node=tmp;
  return node;
}

Node_Exrate *AVL::insertRec(Node_Exrate *&node, ExchangeRate &value, bool &taller)
{
  if(node==NULL){
    node=new Node_Exrate(value);
    taller=true;
    this->count++;
    return node;
  }
  else if(stoi(value.time)==stoi(node->data.time)){
    node->data.BP=value.BP;
    node->data.AP=value.AP;
    taller=false;
    return node;
  }
  else if(stoi(value.time)-stoi(node->data.time)<0){
    node->left=insertRec(node->left,value,taller);
    if(taller){
      if(node->balance==LH){
        node=this->leftBalance(node,taller);
        taller=false;
      }else if(node->balance==EH){
        node->balance=LH;
      }else{
        node->balance=EH;
        taller=false;
      }
    }
  }
  else{
    node->right=insertRec(node->right,value ,taller);
    if(taller){
      if(node->balance==LH){
        node->balance=EH;
        taller=false;
      }else if(node->balance==EH){
        node->balance=RH;
      }else{
        node=this->rightBalance(node,taller);
        taller=false;
      }
    }
  }
  return node;
}
void AVL::insert(ExchangeRate &value)
{
  bool taller=true;
	this->root=this->insertRec(this->root, value, taller);
}
void AVL::clearRec(Node_Exrate *&node)
{
	if (node != NULL)
	{
		this->clearRec(node->left);
		this->clearRec(node->right);
		delete node;
		node = NULL;
	}
}
void AVL::clear()
{
	this->clearRec(this->root);
}

Node_Exrate *AVL::rightBalance(Node_Exrate *&node, bool &taller)
{
  Node_Exrate* right_tree=node->right;
  if(right_tree->balance==RH){
    right_tree->balance=EH;
    node->balance=EH;
    node=rotateLeft(node);
    taller=false;
  }else{
    Node_Exrate* left_tree=right_tree->left;
    if(left_tree->balance==RH){
      node->balance=LH;
      right_tree->balance=EH;
    }else if(left_tree->balance==EH){
      node->balance=EH;
      right_tree->balance=EH;
    }else{
      node->balance=EH;
      right_tree->balance=RH;
    }
    left_tree->balance=EH;
    node->right=this->rotateRight(right_tree);
    node=this->rotateLeft(node);
    taller=false;
  }
  return node;
}
Node_Exrate *AVL::leftBalance(Node_Exrate *&node, bool &taller)
{
  Node_Exrate* left_tree=node->left;
  if(left_tree->balance==LH){
    left_tree->balance=EH;
    node->balance=EH;
    node=rotateRight(node);
    taller=false;
  }else{
    Node_Exrate* right_tree=left_tree->right;
    if(right_tree->balance==LH){
      node->balance=RH;
      left_tree->balance=EH;
    }else if(right_tree->balance==EH){
      node->balance=EH;
      left_tree->balance=EH;
    }else{
      node->balance=EH;
      left_tree->balance=LH;
    }
    right_tree->balance=EH;
    node->left=this->rotateLeft(left_tree);
    node=this->rotateRight(node);
    taller=false;
  }
  return node;
}
Node_Exrate* AVL::removeRec(Node_Exrate *&node, const string &value, bool &shorter, bool &success){
  if(node==NULL){
    shorter=false;
    success=false;
    return NULL;
  }
  if(stoi(value)-stoi(node->data.time)<0){
    node->left=this->removeRec(node->left,value,shorter, success);
    if(shorter)
      node=removeRightBalance(node, shorter);
  }else if(stoi(value)-stoi(node->data.time)>0){
    node->right=this->removeRec(node->right,value,shorter, success);
    if(shorter)
      node=removeLeftBalance(node,shorter);
  }else{
    Node_Exrate* removeNode=node;
    if(node->right==NULL){
      Node_Exrate* newNode=node->left;
      success=true;
      shorter=true;
      delete removeNode;
      return newNode;
    }else if(node->left==NULL){
      Node_Exrate* newNode=node->right;
      success=true;
      shorter=true;
      delete removeNode;
      return newNode;
    }else{
      Node_Exrate*exchPtr=node->left;
      while(exchPtr->right!=NULL){
        exchPtr=exchPtr->right;
      }
      node->data.time=exchPtr->data.time;
      node->left=this->removeRec(node->left,exchPtr->data.time,shorter,success);
      if(shorter)
        node=this->removeRightBalance(node,shorter);
    }
  }
  return node;
}

void AVL::remove(const string &value){
  bool shorter;
  bool success;
  this->root=this->removeRec(this->root,value,shorter,success);
}

Node_Exrate* AVL::removeRightBalance(Node_Exrate *&node, bool &shorter){
  if(node->balance==LH){
    node->balance=EH;
  }else if(node->balance==EH){
    node->balance=RH;
    shorter=false;
  }else{
    Node_Exrate *rightTree=node->right;
    if(rightTree->balance==LH){
      Node_Exrate*leftTree=rightTree->left;
      if(leftTree->balance==LH){
        rightTree->balance=RH;
        node->balance=EH;
      }else if(leftTree->balance==EH){
        node->balance=EH;
        rightTree->balance=EH;
      }else{
        node->balance=LH;
        rightTree->balance=EH;
      }
      leftTree->balance=EH;
      root->right=this->rotateRight(rightTree);
      node=this->rotateLeft(node);
    }else{
      if(rightTree->balance!=EH){
        node->balance=EH;
        rightTree->balance=EH;
      }else{
        node->balance=RH;
        rightTree->balance=LH;
        shorter=false;
      }
      node=this->rotateLeft(node);
    }
  }
  return node;
}
Node_Exrate* AVL::removeLeftBalance(Node_Exrate *&node, bool &shorter){
  if(node->balance==RH){
    node->balance=EH;
  }else if(node->balance==EH){
    node->balance=LH;
    shorter=false;
  }else{
    Node_Exrate *leftTree=node->left;
    if(leftTree->balance==RH){
      Node_Exrate *rightTree=leftTree->right;
      if(rightTree->balance==RH){
        leftTree->balance=LH;
        node->balance=EH;
      }else if(rightTree->balance==EH){
        node->balance=EH;
        leftTree->balance=EH;
      }else{
        node->balance=RH;
        leftTree->balance=EH;
      }
      rightTree->balance=EH;
      root->left=this->rotateLeft(leftTree);
      node=this->rotateRight(node);
    }else{
      if(leftTree->balance!=EH){
        node->balance=EH;
        leftTree->balance=EH;
      }else{
        node->balance=LH;
        leftTree->balance=RH;
        shorter=false;
      }
      node=this->rotateRight(node);
    }
  }
  return node;
}
Node_Exrate* AVL::searchRec(Node_Exrate *&node, const std::string &value){
if(node==NULL) return NULL;
  if(stoi(value)-stoi(node->data.time)<0)
    return searchRec(node->left,value);
  else if(stoi(value)-stoi(node->data.time)>0)
    return searchRec(node->right,value);
  else return node;
}

Node_Exrate* AVL::search( const string &value){
  return this->searchRec(this->root, value);
}

string AVL::findMaxTimeForN(Node_Exrate *&node, string &value){
  if(node==NULL) return "";
  if(stoi(node->data.time)==stoi(value)) return node->data.time;

  else if(stoi(node->data.time)<stoi(value)){
    string k=findMaxTimeForN(node->right,value);
    if(k=="") return node->data.time;
    else return k;
  }
  else if(stoi(node->data.time)>stoi(value)){
    return findMaxTimeForN(node->left,value);
  }
  else return "";
}
string AVL::findMaxTime(string &value){
  return this->findMaxTimeForN(this->root,value);
}
// Currency Things
void CurrencyList::clean(){
  CurrencyNode* currItem=this->head;
  while(currItem!=NULL){
    this->head=currItem->link;
    currItem=NULL;
    delete currItem;
    currItem=this->head;
  }
  this->count=0;
}
void AVL::findRangeTimeRec(Node_Exrate *&node, string &time1, string &time2){
  if(node==NULL){
    return;
  }
  static int i=0;
  if(stoi(time1)-stoi(node->data.time)<0)
    findRangeTimeRec(node->left, time1,time2);
  if(stoi(time1)-stoi(node->data.time)<=0&&stoi(time2)-stoi(node->data.time)>=0){
    myTime.insert(pair<int, string>(i,node->data.time));
    i++;
  }
    
  if(stoi(time2)-stoi(node->data.time)>0)
    findRangeTimeRec(node->right,time1,time2);
}
void AVL::findTime(string &time1,string &time2){
  this->findRangeTimeRec(this->root,time1, time2);
}
CurrencyList::~CurrencyList(){
  this->clean();
}

bool CurrencyList::find(string BC, string QC, int &idx){
  if(this->isEmpty()) {
    idx=-1;
    return false;
  }
  int index=0;
  CurrencyNode* p_Walk=this->head;
  while(p_Walk!=NULL){
    if(p_Walk->currency_data.BC.compare(BC)==0&&p_Walk->currency_data.QC.compare(QC)==0){
      idx=index;
      return true;
    }
    index++;
    p_Walk=p_Walk->link;
  }
  idx=-1;
  return false;
}

int CurrencyList::insert_currency(CurrencyData &a){
  if(this->isEmpty()){
    CurrencyNode* p_New = new CurrencyNode(a);
    this->head=p_New;
    this->count++;
    return 1;
  }else{
    CurrencyNode* p_Walk=this->head;
    while(p_Walk->link!=NULL){
      p_Walk=p_Walk->link;
    }
    CurrencyNode* p_New = new CurrencyNode(a);
    p_Walk->link=p_New;
    this->count++;
    return 1;

  }
  return -1;
}