/**
 * Copyright 2021 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <vector>
#include "micro/coder/opcoders/op_coder.h"
namespace mindspore::lite::micro {

OperatorCoder::~OperatorCoder() {
  node_ = nullptr;
  if (parameter_ != nullptr) {
    free(parameter_);
  }
}

const std::vector<Tensor *> OperatorCoder::input_tensors() const { return input_tensors_; }

const std::vector<Tensor *> OperatorCoder::output_tensors() const { return output_tensors_; }

void OperatorCoder::set_input_tensor_indices(const std::vector<uint32_t> *input_indices) {
  input_tensor_indices_ = *input_indices;
}

void OperatorCoder::set_output_tensor_indices(const std::vector<uint32_t> *output_indices) {
  output_tensor_indices_ = *output_indices;
}

const std::vector<uint32_t> OperatorCoder::input_tensor_indices() const { return input_tensor_indices_; }

const std::vector<uint32_t> OperatorCoder::output_tensor_indices() const { return output_tensor_indices_; }

void OperatorCoder::AddInputNodeIndex(size_t input_node_index) {
  if (!input_node_set_indices_.count(input_node_index)) {
    input_node_set_indices_.insert(input_node_index);
    input_node_indices_.push_back(input_node_index);
  }
}

void OperatorCoder::AddOutputNodeIndex(size_t output_node_index) {
  if (!output_node_set_indices_.count(output_node_index)) {
    output_node_set_indices_.insert(output_node_index);
    output_node_indices_.push_back(output_node_index);
  }
}

const std::vector<size_t> OperatorCoder::input_node_indices() const { return this->input_node_indices_; }
const std::vector<size_t> OperatorCoder::output_node_indices() const { return this->output_node_indices_; }

void OperatorCoder::set_parameter(OpParameter *parameter) { this->parameter_ = parameter; }

size_t OperatorCoder::node_index() const { return node_index_; }

void OperatorCoder::set_thread_num(int thread_num) {
  if (thread_num == 4) {
    this->thread_num_ = thread_num;
    this->thread_num_s_ = "thread_num";
    return;
  } else {
    return;
  }
}
}  // namespace mindspore::lite::micro
