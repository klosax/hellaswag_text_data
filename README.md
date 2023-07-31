## The HellaSwag dataset as simple textfiles

#### Files

`hellaswag_val_full.txt`- All 10042 tasks extracted from the official HellaSwag validation dataset: [hellaswag_val.jsonl](https://github.com/rowanz/hellaswag/blob/master/data/hellaswag_val.jsonl)

`extract_hellaswag.cpp` - Code to extract and preprocess the the original dataset.

#### Preprocessing

See`extract_hellaswag.cpp`

#### Datafile layout:

`['??']` denotes a field processed from the orginal json file and written to datafile as text.

The file contain 6 lines per task:

```
[activity_label'] + ": " + ['ctx']
['label']
['endings'][0]
['endings'][1]
['endings'][2]
['endings'][3]
```
