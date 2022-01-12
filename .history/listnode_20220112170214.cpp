#include <iostream>
#include <cstdlib>

using namespace std;

struct ListNode {
    int val;  // 节点上存储的元素
    ListNode *next;  // 指向下一个节点的指针
    ListNode(int x) : val(x), next(NULL) {}  // 节点的构造函数
};

/*
利用一个缓存节点代表当前判断节点；
若当前判断节点的值需要删除，则当前节点的指针指向下一个节点，并删除缓存节点；
最后一个节点是不会进入while判断条件的。
*/
class Solution {
public:
    //移除链表元素，普通方法
    ListNode* removeElements(ListNode* head, int val) {
        // 删除头结点
        while (head != NULL && head->val == val) { // 注意这里不是if
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }

        // 删除非头结点
        ListNode* cur = head;
        while (cur != NULL && cur->next!= NULL) {
            if (cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        return head;
    }

    //移除链表元素，虚拟头结点法
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0); // 设置一个虚拟头结点
        dummyHead->next = head; // 将虚拟头结点指向head，这样方面后面做删除操作
        ListNode* cur = dummyHead;
        while (cur->next != NULL) {
            if(cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        head = dummyHead->next;
        delete dummyHead;
        return head;
    }

    //反转链表双指针法
    ListNode* reverseList(ListNode* head) {
        ListNode* temp; // 保存cur的下一个节点
        ListNode* cur = head;
        ListNode* pre = NULL;
        while(cur) {
            temp = cur->next;  // 保存一下 cur的下一个节点，因为接下来要改变cur->next
            cur->next = pre; // 翻转操作，cur由指向后一个节点变成指向前一个节点
            // 更新pre 和 cur指针
            pre = cur;
            cur = temp;
        }
        return pre;
    }

    //两两交换链表中的节点
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0); // 设置一个虚拟头结点
        dummyHead->next = head; // 将虚拟头结点指向head，这样方面后面做删除操作
        ListNode* cur = dummyHead;
        while(cur->next != nullptr && cur->next->next != nullptr) {
            ListNode* tmp = cur->next; // 记录临时节点
            ListNode* tmp1 = cur->next->next->next; // 记录临时节点

            cur->next = cur->next->next;    // 步骤一   将虚拟头结点指向第二个节点
            cur->next->next = tmp;          // 步骤二   将第二个节点指向第一个节点
            cur->next->next->next = tmp1;   // 步骤三   此步骤是为了让前面两个节点交换后，原本的第一个节点指向第三个节点

            cur = cur->next->next; // cur移动两位，准备下一轮交换
        }
        return dummyHead->next;
    }

    //删除链表的倒数第N个节点
    //假设该链表有S个节点，快指针和慢指针均从虚拟头结点出发。
    //快指针总共要走S+1步，让快指针先走N+1步，接下来快慢指针同步移动。
    //那么慢指针最终的位置就是S-N点的位置，即倒数第N+1个点，删除第N个节点就是删除慢指针下一个节点。
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* slow = dummyHead;
        ListNode* fast = dummyHead;
        while(n-- && fast != NULL) {
            fast = fast->next;
        }
        fast = fast->next; // fast再提前走一步，因为需要让slow指向删除节点的上一个节点
        while (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return dummyHead->next;
    }

    //链表相交，相交后数据必然是对齐的。所以只要从较短链表的第一位开始查起就行了
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* curA = headA;
        ListNode* curB = headB;
        int lenA = 0, lenB = 0;
        while (curA != NULL) { // 求链表A的长度
            lenA++;
            curA = curA->next;
        }
        while (curB != NULL) { // 求链表B的长度
            lenB++;
            curB = curB->next;
        }
        curA = headA;
        curB = headB;
        // 让curA为最长链表的头，lenA为其长度
        if (lenB > lenA) {
            swap (lenA, lenB);
            swap (curA, curB);
        }
        // 求长度差
        int gap = lenA - lenB;
        // 让curA和curB在同一起点上（末尾位置对齐）
        while (gap--) {
            curA = curA->next;
        }
        // 遍历curA 和 curB，遇到相同则直接返回
        while (curA != NULL) {
            if (curA == curB) {
                return curA;
            }
            curA = curA->next;
            curB = curB->next;
        }
        return NULL;
    }
};

class MyLinkedList {
public:
    // 定义链表节点结构体
    struct LinkedNode {
        int val;
        LinkedNode* next;
        LinkedNode(int val):val(val), next(nullptr){}
    };

    // 初始化链表，如何初始化类参考类的构造函数！！！
    MyLinkedList() {
        _dummyHead = new LinkedNode(0); // 这里定义的头结点 是一个虚拟头结点，而不是真正的链表头结点
        _size = 0;
    }

    // 获取到第index个节点数值，如果index是非法数值直接返回-1， 注意index是从0开始的，第0个节点就是头结点
    int get(int index) {
        if (index > (_size - 1) || index < 0) {
            return -1;
        }
        LinkedNode* cur = _dummyHead->next; //cur初始位于虚拟头节点的下一个节点，也就是实际头节点
        while(index--){ // 如果--index 就会陷入死循环，index等于几，就往后指几次，0就位于头节点，合理！
            cur = cur->next;
        }
        return cur->val;
    }

    // 在链表最前面插入一个节点，插入完成后，新插入的节点为链表的新的头结点
    void addAtHead(int val) {
        LinkedNode* newNode = new LinkedNode(val); //定义一个新头结点，该节点的值为要插入的值
        newNode->next = _dummyHead->next; //新头结点指向
        _dummyHead->next = newNode;
        _size++;
    }

    // 在链表最后面添加一个节点
    void addAtTail(int val) {
        LinkedNode* newNode = new LinkedNode(val); //定义一个新尾结点，该节点的值为要插入的值
        LinkedNode* cur = _dummyHead; 
        while(cur->next != nullptr){ //这个循环负责找到最后一个节点
            cur = cur->next;
        }
        cur->next = newNode; //找到最后一个节点后将其指针指向新尾节点
        _size++;
    }

    // 在第index个节点之前插入一个新节点，例如index为0，那么新插入的节点为链表的新头节点。
    // 如果index 等于链表的长度，则说明是新插入的节点为链表的尾结点
    // 如果index大于链表的长度，则返回空
    void addAtIndex(int index, int val) {
        if (index > _size) { //大于链表长度则返回
            return;
        }
        LinkedNode* newNode = new LinkedNode(val); //定义一个新节点为插入值
        LinkedNode* cur = _dummyHead; //定义一个虚拟头结点
        while(index--) { //找到插入的位置，然后将节点指针连接上即可
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
        _size++;
    }

    // 删除第index个节点，如果index 大于等于链表的长度，直接return，注意index是从0开始的
    void deleteAtIndex(int index) {
        if (index >= _size || index < 0) { //如果大于链表长度或者为负数，则直接返回
            return;
        }
        LinkedNode* cur = _dummyHead; //定义一个虚拟头结点
        while(index--) { //找到删除的位置
            cur = cur ->next;
        }
        LinkedNode* tmp = cur->next; //缓存要删除的节点
        cur->next = cur->next->next; //重新连接指针
        delete tmp; //删除节点
        _size--;
    }

    // 打印链表
    void printLinkedList() {
        LinkedNode* cur = _dummyHead; //定义一个虚拟头结点
        while (cur->next != nullptr) { //只要节点指向不为空，就打印该节点下一个节点的值，并指向下一个节点
            cout << cur->next->val << " ";
            cur = cur->next;
        }
        cout << endl;
    }
private:
    int _size;
    LinkedNode* _dummyHead;

};

int main() {
    Solution solution;
}