class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        a = []
        for root in lists:
            while (root != None):
                a.append(root.val)
                root = root.next
        a.sort()
        if len(a) == 0:
            return None
        root = ListNode(a[0])
        r = root
        for i in range(1, len(a)):
            node = ListNode(a[i])
            r.next = node
            r = node
        return root