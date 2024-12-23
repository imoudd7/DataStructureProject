#include<iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdlib>  
#include <ctime>
#include <iomanip>
using namespace std;



class AvlNode
{
public:
    int Data;
    int yukseklik;
    AvlNode* Left;
    AvlNode* Right;

    AvlNode(int data)
    {
        Data = data;
        Left = Right = NULL;
    }
};




class AvlTree
{
public:

    AvlTree() : Root(NULL) {}

    ~AvlTree()
    {
        if (Root)
        {
            Clean(Root);
            Root = nullptr;
        }
    }

    AvlNode* getRoot()
    {
        return Root;
    }

    bool isFound(int veri)
    {
        return isFound(veri, Root);
    }

    void Add(int veri)
    {
        Root = Add(veri, Root);
    }

    void Delete(int veri)
    {
        Root = Delete(veri, Root);
    }

    int Height()
    {
        return Height(Root);
    }

    void postOrder()
    {
        postOrder(Root);
    }

    void postOrderLeavesRecursive()
    {
        postOrderLeavesRecursive(Root);
        cout << endl;
    }

    int sumOfNonLeaves()
    {
        return sumOfNonLeaves(Root);
    }

    string Ascii(int sum)
    {
        string result;
        if (sum >= 32 && sum <= 126) { // Printable ASCII range
            result = static_cast<char>(sum);
        }
        else {
            result = "Sum is outside the printable ASCII range.";
        }
        return result;
    }

private:
    AvlNode* Root;

    void postOrder(AvlNode* aktif)
    {
        if (aktif) {
            postOrder(aktif->Left);
            postOrder(aktif->Right);
            cout << aktif->Data << "  ";
        }
    }

    int Height(AvlNode* aktifDugum)
    {
        if (!aktifDugum) return -1;
        return 1 + max(Height(aktifDugum->Left), Height(aktifDugum->Right));
    }

    AvlNode* Add(int veri, AvlNode* aktifDugum)
    {
        if (!aktifDugum) return new AvlNode(veri);

        if (veri < aktifDugum->Data) {
            aktifDugum->Left = Add(veri, aktifDugum->Left);
        }
        else if (veri > aktifDugum->Data) {
            aktifDugum->Right = Add(veri, aktifDugum->Right);
        }
        else {
            return aktifDugum;
        }

        aktifDugum->yukseklik = 1 + max(Height(aktifDugum->Left), Height(aktifDugum->Right));

        int balance = dengesizlikYonu(aktifDugum);

        return balanceAndRotate(veri, aktifDugum);
    }

    AvlNode* solaDondur(AvlNode* buyukEbeveyn)
    {
        AvlNode* sagCocuk = buyukEbeveyn->Right;
        buyukEbeveyn->Right = sagCocuk->Left;
        sagCocuk->Left = buyukEbeveyn;
        return sagCocuk;
    }

    AvlNode* sagaDondur(AvlNode* buyukEbeveyn)
    {
        AvlNode* solCocuk = buyukEbeveyn->Left;
        buyukEbeveyn->Left = solCocuk->Right;
        solCocuk->Right = buyukEbeveyn;
        return solCocuk;
    }

    int MaxValue(AvlNode* aktif)
    {
        if (aktif->Right) return MaxValue(aktif->Right);
        return aktif->Data;
    }

    int MinValue(AvlNode* aktif)
    {
        if (aktif->Left)
            return MaxValue(aktif->Left);

        return aktif->Data;
    }

    bool isFound(int aranan, AvlNode* aktif)
    {
        if (!aktif) return false;

        if (aktif->Data < aranan) {
            return isFound(aranan, aktif->Right);
        }
        else if (aktif->Data > aranan) {
            return isFound(aranan, aktif->Left);
        }
        else {
            return true;
        }
    }

    AvlNode* Delete(int veri, AvlNode* aktif)
    {
        if (aktif == 0)
            return 0;

        if (veri < aktif->Data)
        {
            aktif->Left = Delete(veri, aktif->Left);
        }
        else if (veri > aktif->Data)
        {
            aktif->Right = Delete(veri, aktif->Right);
        }
        else
        {
            if (aktif->Left == 0 && aktif->Right == 0)
            {
                delete aktif;
                aktif = 0;
            }
            else if (aktif->Left == 0)
            {
                AvlNode* sil = aktif->Right;
                *aktif = *aktif->Right;
                delete sil;
            }
            else if (aktif->Right == 0)
            {
                AvlNode* sil = aktif->Left;
                *aktif = *aktif->Left;
                delete sil;
            }
            else
            {
                aktif->Data = MinValue(aktif->Right);
                Delete(aktif->Data, aktif->Right);
            }
            return aktif;
        }
    }

    void LeaveSpace(int adet)
    {
        int baslangicBosluk = pow(2, adet) - 1;
        for (int i = 0; i < baslangicBosluk; i++) cout << "  ";
    }

    int dengesizlikYonu(AvlNode* aktif)
    {
        if (!aktif) return 0;
        return Height(aktif->Left) - Height(aktif->Right);
    }

    AvlNode* balanceAndRotate(int veri, AvlNode* aktifDugum)
    {
        int balance = dengesizlikYonu(aktifDugum);

        if (balance > 1 && veri < aktifDugum->Left->Data) {
            return sagaDondur(aktifDugum);
        }

        if (balance < -1 && veri > aktifDugum->Right->Data) {
            return solaDondur(aktifDugum);
        }

        if (balance > 1 && veri > aktifDugum->Left->Data) {
            aktifDugum->Left = solaDondur(aktifDugum->Left);
            return sagaDondur(aktifDugum);
        }

        if (balance < -1 && veri < aktifDugum->Right->Data) {
            aktifDugum->Right = sagaDondur(aktifDugum->Right);
            return solaDondur(aktifDugum);
        }

        return aktifDugum;
    }

    void Clean(AvlNode* aktif)
    {
        if (aktif)
        {
            Clean(aktif->Left);
            Clean(aktif->Right);
            delete aktif;
        }
    }

    void postOrderLeavesRecursive(AvlNode* aktif)
    {
        if (!aktif) return;

        postOrderLeavesRecursive(aktif->Left);
        postOrderLeavesRecursive(aktif->Right);

        if (!aktif->Left && !aktif->Right) {
            cout << aktif->Data << " ";
        }
    }

    int sumOfNonLeaves(AvlNode* aktif)
    {
        if (!aktif) return 0;

        if (!aktif->Left && !aktif->Right)
            return 0;

        int sum = aktif->Data;

        return sum + sumOfNonLeaves(aktif->Left) + sumOfNonLeaves(aktif->Right);
    }


};




class StackNode {
public:
    int Data;
    StackNode* Next;

    StackNode(int veri)
    {
        this->Data = veri;
        Next = nullptr;
    }
};




class Stack {
public:
    Stack() : tepe(NULL) {}

    void Add(int veri)
    {
        StackNode* yeni = new StackNode(veri);
        if (tepe != nullptr) {
            yeni->Next = tepe;
        }
        tepe = yeni;
    }

    void Remove()
    {
        if (tepe != nullptr) {
            StackNode* silinecek = tepe;
            tepe = tepe->Next;
            delete silinecek;
        }
    }

    int getir()
    {
        if (tepe != nullptr) {
            return tepe->Data;
        }
        throw out_of_range("Yigin::Getir(): Yigin Bos");
    }

    int Peak()
    {
        if (tepe != nullptr) {
            return tepe->Data;
        }
        throw out_of_range("Yigin::Zirve(): Yigin Bos");
    }

    bool isItEmpty()
    {
        return tepe == nullptr;
    }

    int getStackSize() const
    {
        return size;
    }

    friend ostream& operator<<(ostream& os, Stack& yigin) {
        cout << setw(5) << "---->";
        StackNode* aktif = yigin.tepe;
        while (aktif != nullptr) {
            cout << setw(5) << aktif->Data << endl << setw(5) << "     ";
            aktif = aktif->Next;
        }
        cout << endl;
        return os;
    }

private:
    StackNode* tepe;
    int size;      

};  




class Line
{
private:
    class ListNode {
    public:
        AvlTree* tree;
        Stack* topOfStack;
        int Sum;
        int Asci;
        ListNode* next;

        ListNode() : tree(new AvlTree()), topOfStack(new Stack()), Sum(0), Asci(0), next(nullptr) {}

        ~ListNode() {
            delete tree;
            delete topOfStack;
        }
    };

    ListNode* head;
    Stack* topOfStack;

    void RemoveLine(ListNode* node)
    {
        if (node == head)
        {
            head = node->next;
        }
        else
        {
            ListNode* current = head;
            while (current && current->next != node)
            {
                current = current->next;
            }

            if (current)
            {
                current->next = node->next;
            }
        }

        delete node->topOfStack;
        delete node->tree;
        delete node;
    }

public:
    Line() : head(nullptr), topOfStack(new Stack()) {}

    ~Line()
    {
        while (head)
        {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }

        delete topOfStack;
    }

    void Display1(Line& line)
    {
        Display(line);
    }

    void ProcessFile(string filename)
    {
        ifstream file(filename);

        if (!file.is_open())
        {
            cerr << "Unable to open file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            AddLine(line);
        }

        file.close();
    }

    void AddLine(const string& lineData)
    {
        ListNode* newNode = new ListNode();
        headInsert(newNode);

        istringstream iss(lineData);
        int value;
        while (iss >> value)
        {
            newNode->tree->Add(value);
        }

        postOrderTraversalWithActions(newNode->tree->getRoot(), newNode);

        newNode->Sum = newNode->tree->sumOfNonLeaves();

        newNode->Asci = calculateAscii(newNode->Sum);
    }

    void headInsert(ListNode* newNode)
    {
        newNode->next = head;
        head = newNode;
    }

    void postOrderTraversalWithActions(AvlNode* aktif, ListNode* currentLine)
    {
        if (aktif)
        {
            postOrderTraversalWithActions(aktif->Left, currentLine);
            postOrderTraversalWithActions(aktif->Right, currentLine);

            if (!aktif->Left && !aktif->Right)
            {
                AddLeaveToStack(aktif, currentLine);
            }
        }
    }

    void Display(Line& line)
    {
        srand(static_cast<unsigned int>(time(nullptr)));

        if (!head)
        {
            cout << "No characters to display." << endl;
            return;
        }

        vector<char> characters;
        ListNode* current = head;
        while (current)
        {
            characters.push_back(static_cast<char>(current->Asci));
            current = current->next;
        }

        for (int i = characters.size() - 1; i >= 0; --i)
        {
            cout << characters[i];
        }
        cout << endl;

        for (int i = characters.size() - 1; i >= 0; --i)
        {
            if (characters.size() > 1)
            {
                int indexToDelete = rand() % characters.size();
                char deletedChar = characters[indexToDelete];

                characters.erase(characters.begin() + indexToDelete);

                system("cls");

                for (int i = characters.size() - 1; i >= 0; --i)
                {
                    cout << characters[i];
                }

                if (characters.size() == 1) {
                    // إذا كان هناك حرف واحد فقط، قم بطباعة التصميم المطلوب
                    cout << "=======================" << endl;
                    cout << "|                      |" << endl;
                    cout << "|                      |" << endl;
                    cout << "|    Son Karakter :  " << characters[0] << " |" << endl;
                    cout << "|    AVL No       : " << rand() % 900 + 100 << "|" << endl;
                    cout << "|                      |" << endl;
                    cout << "|                      |" << endl;
                    cout << "========================" << endl;
                    break;
                }
            }
        }

        cout << endl;
    }
 
    void AddLeaveToStack(AvlNode* node, ListNode* currentLine)
    {
        currentLine->topOfStack->Add(node->Data);
    } 

    char calculateAscii(int sum)
    {
        return sum % (90 - 65 + 1) + 65;
    }

    void DisplayCharactersReversed()
    {
        if (!head)
        {
            cout << "No characters to display." << endl;
            return;
        }

        vector<char> characters;
        ListNode* current = head;
        while (current)
        {
            characters.push_back(static_cast<char>(current->Asci));
            current = current->next;
        }

        for (int i = characters.size() - 1; i >= 0; --i)
        {
            cout << characters[i];
        }

        cout << endl;
    }

    Stack* getStack()
    {
        return topOfStack;
    }

    void RemoveSmallest()
    {
        if (!head) {
            cout << "No lines to remove." << endl;
            return;
        }

        int smallestValue = numeric_limits<int>::max();  

        ListNode* current = head;
        ListNode* smallestNode = nullptr;

        while (current)
        {
            if (!current->topOfStack->isItEmpty())
            {
                int topValue = current->topOfStack->Peak();
                if (topValue < smallestValue)
                {
                    smallestValue = topValue;
                    smallestNode = current;
                }
            }

            current = current->next;
        }

        if (smallestNode)
        {
            smallestNode->topOfStack->Remove();
        }
    }

    void RemoveBiggest()
    {
        if (!head) {
            cout << "No lines to remove." << endl;
            return;
        }

        int biggestValue = numeric_limits<int>::min();

        ListNode* current = head;
        ListNode* biggestNode = nullptr;

        while (current)
        {
            if (!current->topOfStack->isItEmpty())
            {
                int topValue = current->topOfStack->Peak();
                if (topValue > biggestValue)
                {
                    biggestValue = topValue;
                    biggestNode = current;
                }
            }

            current = current->next;
        }

        // حذف العنصر الأكبر من الستاك المحدد
        if (biggestNode)
        {
            biggestNode->topOfStack->Remove();
        }
    }
};



   



int main()
{
    Line L1;
    L1.ProcessFile("Veri.txt");
    L1.Display1(L1);



    system("pause>0");
    return 0;
}