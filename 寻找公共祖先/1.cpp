/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        stack<ListNode*>s1;
        stack<ListNode*>s2;
        while(pHead1)
        {
            s1.push(pHead1);
            pHead1=pHead1->next;
        }
        while(pHead2)
        {
            s2.push(pHead2);
            pHead2=pHead2->next;
        }
        ListNode*cur=NULL;
        while(!s1.empty()&&!s2.empty())
        {
            
            if(s1.top()==s2.top())
            {
                cur=s1.top();
                s1.pop();
                s2.pop();
            }
            else
                break;
        }
        return cur;
    }
};