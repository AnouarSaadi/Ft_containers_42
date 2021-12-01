# Ft_containers_42

   <!-- Tree-Delete(T, z) -->
     <!-- if z.left = NIL then -->
       <!-- Subtree-Shift(T, z, z.right) -->
     <!-- else if z.right = NIL then -->
       <!-- Subtree-Shift(T, z, z.left) -->
     <!-- else -->
       <!-- y := Tree-Successor(z) -->
       <!-- if y.parent ≠ z then -->
         <!-- Subtree-Shift(T, y, y.right) -->
         <!-- y.right := z.right -->
         <!-- y.right.parent := y -->
         <!-- end if -->
       <!-- Subtree-Shift(T, z, y) -->
       <!-- y.left := z.left -->
       <!-- y.left.parent := y -->
     <!-- end if -->

   <!-- Subtree-Shift(T, u, v) -->
     <!-- if u.parent = NIL then -->
       <!-- T.root := v -->
     <!-- else if u = u.parent.left then -->
       <!-- u.parent.left := v -->
     <!-- else -->
       <!-- u.parent.right := v -->
     <!-- end if -->
     <!-- if v ≠ NIL then -->
       <!-- v.parent := u.parent -->
     <!-- end if -->