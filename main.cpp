#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Root
{
protected:
    string name;
    Root* parent;
    int readyIndex;
public:
    vector<Root*> childrens;

    Root(string name, Root* ptr , int index)
    {
        setName(name);
        setParent(ptr);
        setReadyIndex(index);
    }

    int getReadyIndex()
    {
        return readyIndex;
    }

    string getName()
    {
        return name;
    }

    Root* getParent()
    {
        return parent;
    }

    void setReadyIndex(int index)
    {
        this->readyIndex = index;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setParent(Root* newParent)
    {
        parent = newParent;
    }

    Root* FindObj(string findName)
    {
        Root* returnPtr = nullptr;
        if (this->getName() == findName)
            return this;
        if (!this->childrens.empty())
        {
            for (int i = 0; i < this->childrens.size(); i ++)
            {
                if (this->childrens[i]->getName() == findName)
                    return this->childrens[i];
                if (!this->childrens[i]->childrens.empty())
                    returnPtr = this->childrens[i]->FindObj(findName);
                if (returnPtr != nullptr)
                    break;
            }
        }
        return returnPtr;
    }

    void printTree()
    {
        static int spaceCounter = 0;

        cout<<endl;
        for (int i = 0; i < spaceCounter;i++)
            cout<<"    ";
        cout<<this->getName();

        if (!this->childrens.empty())
        {
            spaceCounter++;
            for (int i = 0; i < this->childrens.size(); i++)
            {
                if (!this->childrens[i]->childrens.empty())
                {
                    this->childrens[i]->printTree();
                }
                else
                {
                    cout<<endl;
                    for (int i = 0; i < spaceCounter;i++)
                        cout<<"    ";
                    cout<<this->childrens[i]->getName();
                }
            }
            spaceCounter--;
        }
    }
    Root* findObjByCord(string parentName)
    {
        Root* tmpParent = nullptr;
        int rootCounter = 0;
        string tmpName;
        for (int i = 1; i < parentName.size();i++)
        {
            tmpName = "";
            while (parentName[i] != '/' && i < parentName.size())
            {
                tmpName += parentName[i];
                i++;
            }
            if (this->getName() == tmpName && rootCounter == 0)
            {
                tmpParent = this;
                rootCounter++;
                continue;
            }

            if (this->childrens.empty())
                tmpParent = nullptr;

            if (tmpParent != nullptr )
            {
                for (int j = 0; j < tmpParent->childrens.size(); j++)
                {
                    if (tmpParent->childrens[j]->getName() == tmpName)
                    {
                        tmpParent = tmpParent->childrens[j];
                        break;
                    }
                    if (j == tmpParent->childrens.size() - 1)
                        tmpParent = nullptr;
                }
            }
        }
        return tmpParent;
    }
    void finder()
    {
        string cords;
        cin>>cords;
        Root* obj;
        while (cords != "//")
        {
            cout<<endl;
            if (cords[0] == cords[1])
            {
                cords = cords.substr(2,cords.size() - 2);
                obj = FindObj(cords);
            }
            else
                obj = findObjByCord(cords);
            if (obj == nullptr)
                cout<<cords<<" Object not found";
            else
                cout<<cords<<" Object name: "<<obj->getName();
            cin>>cords;
        }
    }
};

class Fourth:public Root
{
public:
    Fourth(string name, Root* ptr,int index):Root(name,ptr,index){}
};

class Second:public Root
{
public:
    Second(string name, Root* ptr,int index):Root(name,ptr,index){}
};

class Third:public Root
{
public:
    Third(string name, Root* ptr,int index):Root(name,ptr,index){}
};

class Builder: public Root
{
public:

    Builder(nullptr_t i):Root("",i,1){};

    void buildTree()
    {
        string parentCords, childName;
        int classNumber, redyIndex;
        cin>>parentCords;
        this->name = parentCords;
        this->parent = nullptr;
        Root* tmpParent;
        Root* nextChild;

        while (true)
        {
            cin>>parentCords;
            if (parentCords == "endtree")
                return;
            cin>>childName>>classNumber>>redyIndex;

            tmpParent = findObjByCord(parentCords);

            if (tmpParent != nullptr)
            {
                switch (classNumber)
                {
                    case 2:
                        nextChild = new Second(childName,tmpParent,redyIndex);
                        break;
                    case 3:
                        nextChild = new Third(childName,tmpParent,redyIndex);
                        break;
                    case 4:
                        nextChild = new Fourth(childName,tmpParent,redyIndex);
                        break;
                }
                tmpParent->childrens.push_back(nextChild);
            }
        }
    }

    int print()
    {
        cout<<"Object tree";
        this->printTree();
        this->finder();
        return 0;
    }
};

int main()
{
    Builder builder(nullptr);
    builder.buildTree();
    return builder.print();
}
