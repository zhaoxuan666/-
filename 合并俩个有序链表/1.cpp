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
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
       ListNode*NewList,*List;
        if(pHead1==NULL)
            return pHead2;
        if(pHead2==NULL)
            return pHead1;
        if(pHead1->val<=pHead2->val)
        {
            NewList=List=pHead1;
            pHead1=pHead1->next;
        }
        else
        {
            NewList=List=pHead2;
            pHead2=pHead2->next;
        }
        while(pHead1&&pHead2)
        {
            if(pHead1->val<=pHead2->val)
            {
                List->next=pHead1;
                pHead1=pHead1->next;
                List=List->next;
            }
            else
            {
                List->next=pHead2;
                pHead2=pHead2->next;
                List=List->next;
            }
        }
        if(pHead1==NULL)
            List->next=pHead2;
        if(pHead2==NULL)
            List->next=pHead1;
        return NewList;
    }
};