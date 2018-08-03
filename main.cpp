#include <iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<string>
using namespace std;
vector<string> helpList;
vector<string> path;
struct Node {
    Node* parent;//���ڵ�
    Node* headSon;//��һ���ӽڵ�
    Node* sibiling;//��һ���ֵܽڵ�
    string name;
    vector<string> content;
    int permission;
    int type;//0���ļ��У�1���ļ�
    Node() {
        parent=0;
        headSon=0;
        sibiling=0;
        permission=0;
        type=0;
    }
    bool createFolder(const string& newName,const int level) {
        Node* exist=this->isExist(newName);
        if (exist) {
            printf("�ļ����ļ����Ѵ���\n");
            return false;
        }
        Node* folder=new Node();
        folder->name=newName;
        Node* tmp=this->headSon;
        this->headSon=folder;
        folder->sibiling=tmp;
        folder->parent=this;
        folder->permission=level;
        return true;
    }
    bool createFile(const string& newName,const string& newContent,const int level) {
        Node* exist=this->isExist(newName);
        if (exist) {
            printf("�ļ����ļ����Ѵ���\n");
            return false;
        }
        Node* file=new Node();
        file->name=newName;
        file->type=1;
        file->content.push_back(newContent);
        Node* tmp=this->headSon;
        this->headSon=file;
        file->sibiling=tmp;
        file->parent=this;
        file->permission=level;
        return true;
    }
    bool addContent(const string& findName,const string&  newContent,const int level) {
        Node* now=this->headSon;
        while (now!=0) {
            if (now->name==findName) {
                if (now->type!=1) {
                    cout<<"������Ĳ����ļ��������ļ�����"<<endl;
                    return false;
                }
                if (now->permission>level){
                    cout<<"Ȩ�޲���"<<endl;
                    return false;
                }
                now->content.push_back(newContent);
                return true;
            }
        }
        cout<<"�ļ�������"<<endl;
        return false;
    }
    bool openFile(const string& findName,const int level) {
        Node* now=this->headSon;
        while (now!=0) {
            if (now->name==findName) {
                if (now->type!=1) {
                    cout<<"������Ĳ����ļ��������ļ�����"<<endl;
                    return false;
                }
                if (now->permission>level){
                    cout<<"Ȩ�޲���"<<endl;
                    return false;
                }
                for (int i=0; i<now->content.size(); i++) {
                    cout<<i<<" "<<now->content[i]<<endl;
                }
                return true;
            }
        }
        cout<<"�ļ�������"<<endl;
        return false;
    }
    bool insertFile(const string& findName,const int pos,const string& newContent,const int level){
        Node* now=this->headSon;
        while (now!=0) {
            if (now->name==findName) {
                if (now->type!=1) {
                    cout<<"������Ĳ����ļ��������ļ�����"<<endl;
                    return false;
                }
                if (now->permission>level){
                    cout<<"Ȩ�޲���"<<endl;
                    return false;
                }
                if (pos>=now->content.size()) {
                    cout<<"���������̫��"<<endl;
                    return false;
                }
                now->content.insert(now->content.begin()+pos,newContent);
                return true;
            }
        }
        cout<<"�ļ�������"<<endl;
        return false;
    }
    Node* isExist(const string& findName) {
        Node* now=this->headSon;
        while(now!=0) {
            if (now->name==findName) {
                return now;
            }
            now=now->sibiling;
        }
        return 0;
    }
    void listAll() {
        Node* now=this->headSon;
        while (now!=0) {
            cout<<now->name<<" ";
            if (now->type==0) cout<<"�ļ���"<<endl;
            else cout<<"�ļ�"<<endl;
            now=now->sibiling;
        }
    }
    Node* enter(const string& cdName,const int level) {
        Node* now=this->headSon;
        while(now!=0) {
            if (now->name==cdName) {
                if (now->permission>level){
                    cout<<"Ȩ�޲���"<<endl;
                    return false;
                }
                if (now->type==0)
                    return now;
                else {
                    cout<<"��Ҫ����Ĳ����ļ��У��޷�����\n"<<endl;
                    return 0;
                }
            }
            now=now->sibiling;
        }
        cout<<"�Ҳ����ļ��У��޷�����\n"<<endl;
        return 0;
    }
    Node* goBack() {
        if (this->parent==0) return this;
        else {
            return this->parent;
        }
    }
    bool deleteByName(const string& delName,const int level) {
        if (this->headSon->name==delName) {
            Node* tmp=this->headSon->sibiling;
            delete this->headSon;
            this->headSon=tmp;
            return true;
        }
        Node* now=this->headSon->sibiling;
        Node* pre=this->headSon;
        while (now!=0) {
            if (now->name==delName) {
                if (now->permission>level){
                    cout<<"Ȩ�޲���"<<endl;
                    return false;
                }
                Node* tmp=now->sibiling;
                delete now;
                pre->sibiling=tmp;
                return true;
            }
            pre=now;
            now=now->sibiling;
        }
        //printf("�Ҳ���Ҫɾ�����ļ����ļ���\n");
        return false;
    }
    ~Node() {
        if (this->type==1) {
            //pass
        } else {
            Node* now=this->headSon;
            while(now!=0) {
                Node* next=now->sibiling;
                delete now;
                now=next;
            }
            this->headSon=0;
        }
    }

};

struct User{
    string userName;
    string password;
    int level;
    User(){
    }
    User(const string& userName,const string&password,const int level){
        this->userName=userName;
        this->password=password;
        this->level=level;
    }
};
vector<User>userList;
bool createUser(const string& userName,const string&password,const int level,const int nowLevel){
    if (level>nowLevel){
        cout<<"�޷������ȵ�ǰ�û�Ȩ�޸��ߵ��û�"<<endl;
        return false;
    }
    for (int i=0;i<userList.size();i++){
        if (userList[i].userName==userName){
            cout<<"���û��Ѵ���"<<endl;
            return false;
        }
    }
    userList.push_back(User(userName,password,level));
    cout<<"�û������ɹ�";
    return true;
}
void listUser(){
    for (int i=0;i<userList.size();i++){
        cout<<"�û�����"<<userList[i].userName<<" Ȩ�ޣ�"<<userList[i].level<<endl;
    }
}
User* findUser(const string& userName,const string&password){
    for (int i=0;i<userList.size();i++){
        if (userList[i].userName==userName){
            if (userList[i].password==password){
                return &userList[i];
            } else {
                cout<<"���벻��ȷ"<<endl;
                return 0;
            }

        }
    }
    cout<<"���û�������"<<endl;
    return 0;
}
void initHelp() {
    helpList.push_back("help:��ѯָ���");
    helpList.push_back("createfile/touch:�����ļ�");
    helpList.push_back("createfolder/mkdir:�����ļ���");
    helpList.push_back("list/ls:�г����������ļ����ļ���");
    helpList.push_back("enter/cd:�����ļ���");
    helpList.push_back("goback:�ص���һ��");
    helpList.push_back("delete/rm:ɾ���ļ����ļ���");
    helpList.push_back("open:�Ķ��ļ�");
    helpList.push_back("add:��ĳ���ļ���׷������");
    helpList.push_back("insert:��ĳ���ļ����м��������");
    helpList.push_back("exit:�˳�����");
    helpList.push_back("createuser�������û�");
    helpList.push_back("listuser:�г������û�");
    helpList.push_back("login:��¼��ĳ���û�");
}

void getHelp() {
    for (int i=0; i<helpList.size(); i++) cout<<helpList[i]<<endl;
}
int main() {
    Node* root=new Node();
    Node* now=root;
    userList.push_back(User("guest","guest",0));
    userList.push_back(User("root","root",255));
    initHelp();
    string order,value1,value2;
    cout<<"����help��ȡ�������顣��ʼ�û���guest��������guest�����г�������Ա�˺�root������root"<<endl;
    User* nowUser=&userList[0];
    while(true) {
        cout<<"~";
        for (int i=0; i<path.size(); i++) {
            cout<<"/"<<path[i];
        }
        cout<<"["<<nowUser->userName<<" Ȩ��:"<<nowUser->level<<"]";
        cout<<": ";
        cin>>order;
        if (order=="help") {
            getHelp();
        } else if (order=="createfile"||order=="touch") {
            cout<<"�����ļ���: ";
            cin>>value1;
            if (now->isExist(value1)!=0) {
                cout<<"�ļ��Ѵ���"<<endl;
            } else {
                cout<<"�����½��ļ����ݣ�";
                cin.get();
                getline(cin,value2);
                if (now->createFile(value1,value2,nowUser->level)) {
                    cout<<"�ļ������ɹ�"<<endl;
                }
            }
        } else if (order=="createfolder"||order=="mkdir") {
            cout<<"�����ļ������ƣ�";
            cin>>value1;
            if (now->createFolder(value1,nowUser->level)) {
                cout<<"�ļ��д����ɹ�"<<endl;
            }
        } else if (order=="list"||order=="ls") {
            now->listAll();
        } else if (order=="enter"||order=="cd") {
            cin>>value1;
            Node* next=now->enter(value1,nowUser->level);
            if (next!=0) {
                path.push_back(value1);
                now=next;
            }
        } else if (order=="goback") {
            if (now!=root) path.pop_back();
            now=now->goBack();
        } else if (order=="delete"||order=="rm") {
            cin>>value1;
            if (now->deleteByName(value1,nowUser->level)) {
                cout<<"ɾ���ɹ�"<<endl;
            } else {
                cout<<"ɾ��ʧ��"<<endl;
            }
        } else if (order=="open") {
            cout<<"�����ļ�����";
            cin>>value1;
            now->openFile(value1,nowUser->level);
        } else if (order=="add") {
            cout<<"�����ļ�����";
            cin>>value1;
            cout<<"׷�ӵ��ļ�����";
            cin.get();
            getline(cin,value2);
            now->addContent(value1,value2,nowUser->level);
        } else if (order=="insert"){
            cout<<"�����ļ�����";
            cin>>value1;
            if (now->openFile(value1,nowUser->level)){
                int vt;
                cout<<"����Ҫ������һ����¼֮ǰ:";
                cin>>vt;
                cout<<"����Ҫ���������"<<endl;
                cin.get();
                getline(cin,value2);
                now->insertFile(value1,vt,value2,nowUser->level);
            }
        } else if (order=="exit") {
            break;
        } else if (order=="login") {
            cout<<"�������û�����";
            cin>>value1;
            cout<<"���������룺";
            cin>>value2;
            User* tmp=findUser(value1,value2);
            if (tmp!=0){
                nowUser=tmp;
            }
        } else if (order=="createuser"){
            cout<<"������Ҫ�������û���"<<endl;
            cin>>value1;
            cout<<"������Ҫ�����û�������"<<endl;
            cin>>value2;
            cout<<"������Ҫ�����û���Ȩ�ޡ����ܸ��ڵ�ǰ�û���Ȩ��"<<endl;
            int vt;
            cin>>vt;
            createUser(value1,value2,vt,nowUser->level);
        } else if (order=="listuser") {
            listUser();
        }
        else {
            cout<<"�޷�ʶ������"<<endl;
        }

    }

    return 0;
}
