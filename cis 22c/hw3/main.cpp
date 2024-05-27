// Kanan Ibadzade - CIS22C - HW3 


Node* BST::getPrev(Node* from)
{ 
    Node* currNode = NULL;
    if (from->LHC) {  
        currNode = from->LHC;
        while (currNode->RHC)  currNode = currNode->RHC; 
        return (currNode);
    }
  
    if (!(currNode = from->parent)) return (NULL);
   
    while (currNode->parent) {
        if (currNode == currNode->parent->LHC) {
            currNode = currNode->parent;
        }
        else {
        break;
        }
    }
    
    return (currNode->parent);
}

// TREE WALKING RULES:

// 1. If the left child (LHC) exists, 
// go to the rightmost child of the left subtree. 
// Check if there's a left child. 
// If there is, go to the rightmost child (the maximum value in the left subtree) of the current node. 

// 2. if there is no left child and the parent exists, return the parent. 
// If there is no left child, but a parent exists, you've reached the minimum value of the current subtree. 
// then you return the parent node because it's the "previous" node.

// 3. use the grandparent. While there is a parent node, continue moving up the tree while there is a parent node. 
// Check if the current node is the left child of its parent. 
// If it is, move up to the parent because you are still looking for the "previous" node. 
// If the current node is the right child of its parent, 
// then this parent is the "previous" node, and you can break out of the loop.

