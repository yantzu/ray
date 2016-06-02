#ifndef ORCHESTRA_COMPUTATIONGRAPH_H
#define ORCHESTRA_COMPUTATIONGRAPH_H

#include <iostream>
#include <limits>

#include "orchestra/orchestra.h"
#include "orchestra.grpc.pb.h"
#include "types.pb.h"

// used to represent the root operation (that is, the driver code)
const OperationId ROOT_OPERATION = std::numeric_limits<OperationId>::max();
// used to represent the absence of an operation
const OperationId NO_OPERATION = std::numeric_limits<OperationId>::max() - 1;

class ComputationGraph {
public:
  // Add an operation to the computation graph, this returns the OperationId for
  // the new operation. This method takes ownership over operation.
  OperationId add_operation(std::unique_ptr<Operation> operation);
  // Return the task corresponding to a particular OperationId. If operationid
  // corresponds to a push, then fail.
  const Task& get_task(OperationId operationid);
private:
  // maps an OperationId to the corresponding task or push
  std::vector<std::unique_ptr<Operation> > operations_;
  // spawned_operations_[operationid] is a vector of the OperationIds of the
  // operations spawned by the task with OperationId operationid
  std::vector<std::vector<OperationId> > spawned_operations_;
};

#endif
