// Copyright di ISAAC

/**
 * Documentazione in doxygen
 */
service TaskPlanning {
  bool stepTo(1:double x, 2:double y, 3: double theta);
  bool grasp(1:i32 blockId);
  bool place(1:i32 blockId, 2:i32 objId);
}
