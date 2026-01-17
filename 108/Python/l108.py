class TreeNode(object):
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
    
    def add_child(self, child, direction):
        match direction:
            case "left":
                self.left = child
            case "right":
                self.right = child
            case _:
                print("Did something happen?")
    
    def value(self, value):
        self.val = value


node3 = TreeNode()
node2 = TreeNode()
node1 = TreeNode()
node4 = TreeNode()
node5 = TreeNode()
node6 = TreeNode()

node3.value(3)
node3.add_child(node2, "left")
node3.add_child(node5, "right")

node2.value(2)
node2.add_child(node1, "left")
node1.value(1)

node4.value(4)
node5.value(5)
node5.add_child(node4, "left")
node5.add_child(node6, "right")
node6.value(6)

tree = [node1, node2, node3, node4, node5, node6]

def printTree(tree):
    for t in tree:
        print(t.val)

printTree(tree)

class Solution(object):
    def sortedArrayToBST(self, nums):
        """
        :type nums: List[int]
        :rtype: Optional[TreeNode]
        """
        if nums == []:
            return
        root = TreeNode(nums[len(nums)//2])
        root.left = self.sortedArrayToBST(nums[:len(nums)//2])
        root.right = self.sortedArrayToBST(nums[len(nums)//2+1:])
        return root