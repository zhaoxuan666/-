/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        ListNode*head=new ListNode(0);
        head->next=pHead;
        ListNode*cur=pHead;
        ListNode*prev=head;
        while(cur&&cur->next)
        {
            if(cur->val==cur->next->val)
            {
                int v=cur->val;
                while(cur&&cur->val==v)
                    cur=cur->next;
                prev->next=cur;
            }
            else{
                prev=cur;
                cur=cur->next;
            }
        }
        return head->next;
    }
};