ListNode* deleteDuplication(ListNode* pHead)
    {
        ListNode*NewList=new ListNode(-1);
        NewList->next=pHead;
        ListNode*List=NewList;
        ListNode*cur=pHead;
        ListNode*N;
        while(cur&&cur->next)
        {
            N=cur->next;
            if(cur->val==N->val)
            {
                while(N&&cur->val==N->val)
                {
                    N=N->next;
                }
                List->next=N;
                cur=N;
            }
            else{
                List=cur;
                cur=cur->next;
            }
        }
        return NewList->next;
    }