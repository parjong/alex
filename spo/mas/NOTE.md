# Goal

Let's design and implement an extensible toolkit for NN model characteristics analysis.

The characteristics of interest
- The number of compute operations
- The amount of data transfer (in bytes) under various execution scheme

## Requirements

### Goal

ID  | Description
--- | ---
IM1 | This toolkit SHOULD allow users to analyze TFLITE models (.tflite)
IM2 | This toolkit SHOULD allow users to analyze ONNX models (.onnx)
AR1 | This toolkit SHOULD allow users to analyze the impact of various _quantization_ schemes
AR2 | This toolkit SHOULD allow users to analyze the impact of _prunning_ (or _compression_)
EX1 | This toolkit SHOULD allow users to introduce a new analysis

### Non-Goal

- This toolkit is not designed to analyze the impact of model architecture changes.
- This toolkit is not designed to analyze the impact of model shape changes.
- This toolkit is not designed to analyze models with control primitives (e.g. branch, loop)
  - This toolkit is designed to analyze a directed acyclic graph.

## Brainstorming

This toolkit provides a set of importers to meet IM1 and IM2 requirement.
These importers emit a _uniform_ **in-memory** representation.

**NOTE** Why in-memory representation?

It is non-trival to encode tensor values in a file.
Instead, let's implement a script to export a textual (e.g. YAML) file, which makes it easy to view the overall summary.
WARNING! DO NOT use this textual file for serialization.

The importer output SHOULD be easy to **modify** (for some extent) to meet AR1 and AR2 requirement.
- Especially value-level properties

The impact of these decisions
1. Analyzer SHOULD be aware of framework file format.
2. A script SHOULD be able to update avgbit!

**Usecase** A user queries the amount of data transfer from the importer output with _node-by-node_ execution.
**Design Impact**
- The importer output SHOULD provide the size of input/output of each _operation_(?).

```
mcs-analyze -m <path/to/mcs> <path/to/1st/analysis/script> ... <path/to/Nth/analysis/script>
```

## Files

- model (or workload) specification
- model analysis script

## Component

- importer (per framework)
- analysis runner (one)
- analysis scripts
  - the amount of data transfer (per execution scheme)
  - the number of operations (per opset)

**NOTE** The number of opset >= the number of framework.

A framework can define multiple opsets. For example, ONNX uses opset versioning.
