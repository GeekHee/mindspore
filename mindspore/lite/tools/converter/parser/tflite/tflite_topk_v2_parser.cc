/**
* Copyright 2020 Huawei Technologies Co., Ltd
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* distributed under the License is distributed on an AS
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "tools/converter/parser/tflite/tflite_topk_v2_parser.h"
#include <vector>
#include <memory>
#include <map>

namespace mindspore {
namespace lite {
STATUS TfliteTopKV2Parser::Parse(const std::unique_ptr<tflite::OperatorT> &tflite_op,
                                 const std::vector<std::unique_ptr<tflite::TensorT>> &tflite_tensors,
                                 const std::vector<std::unique_ptr<tflite::BufferT>> &tflite_model_buffer,
                                 schema::CNodeT *op,
                                 std::vector<int32_t> *tensors_id,
                                 std::vector<schema::Format> *tensors_format,
                                 std::map<int, int>  *tensors_id_map) {
  MS_LOG(DEBUG) << "parse TfliteTopKV2Parser";

  if (op == nullptr) {
    MS_LOG(ERROR) << "op is null";
    return RET_NULL_PTR;
  }
  op->primitive = std::make_unique<schema::PrimitiveT>();
  if (op->primitive == nullptr) {
    MS_LOG(ERROR) << "op->primitive is null";
    return RET_NULL_PTR;
  }

  std::unique_ptr<schema::TopKT> attr = std::make_unique<schema::TopKT>();

  attr->sorted = true;
  std::vector<int32_t> k;
  if (GetTfliteData(tflite_op->inputs[1], tflite_tensors, tflite_model_buffer, k)) {
    MS_LOG(ERROR) << "get topKV2 -> k failed";
    return RET_ERROR;
  }
  attr->k = k.front();

  op->primitive->value.type = schema::PrimitiveType_TopK;
  op->primitive->value.value = attr.release();

  AddOpInput(op, tensors_id, tensors_format, tensors_id_map,
             tflite_op->inputs[0], tensors_id->size(), tflite_tensors.size(), schema::Format_NHWC);
  for (int i = 0; i < tflite_op->outputs.size(); i++) {
    AddOpOutput(op, tensors_id, tensors_format, tensors_id_map,
                tflite_op->outputs[i], tensors_id->size(), tflite_tensors.size(), schema::Format_NHWC);
  }
  return RET_OK;
}

TfliteNodeRegister g_tfliteTopKV2Parser("TopKV2", new TfliteTopKV2Parser());
}  // namespace lite
}  // namespace mindspore
