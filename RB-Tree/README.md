# Red-Black Tree Insertion Fix

## Standard Insertion

Let `x` be the newly inserted node.

1. Perform standard BST insertion and make the color of the newly inserted node **RED**.
2. If `x` is the root, change its color to **BLACK** (as the black height of the complete tree increases by 1).
3. Otherwise, proceed with the following steps if `x`’s parent is **not BLACK** or if `x` is not the root.

## Fixing Violations

### Case 1: `x`’s Uncle is RED

- Change the color of the parent and uncle to **BLACK**.
- Change the color of the grandparent to **RED**.
- Set `x = x`’s grandparent and repeat steps 2 and 3 for the new `x`.

**Diagram:**

<p align="center">
    <img src="RBTree-schemes/redBlackCase2.png" width="75%">
</p>

---

### Case 2: `x`’s Uncle is BLACK

#### Determine the Configuration:

1. **Left Left Case**: `p` is the left child of `g`, and `x` is the left child of `p`.
2. **Left Right Case**: `p` is the left child of `g`, and `x` is the right child of `p`.
3. **Right Right Case**: Mirror of **Left Left Case**.
4. **Right Left Case**: Mirror of **Left Right Case**.

Set `x = x`’s parent and repeat steps 2 and 3 for the new `x`.

**Operations for Four Cases When Uncle is BLACK:**

- **Left Left Case:**
<p align="center">
    <img src="RBTree-schemes/redBlackCase3a1.png" width="75%">
</p>

- **Left Right Case:**
<p align="center">
    <img src="RBTree-schemes/redBlackCase3b.png" width="75%">
</p>

- **Right Right Case:**
<p align="center">
    <img src="RBTree-schemes/redBlackCase3c.png" width="75%">
</p>

- **Right Left Case:**
<p align="center">
    <img src="RBTree-schemes/redBlackCase3d.png" width="75%">
</p>
