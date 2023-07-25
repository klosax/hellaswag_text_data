## The HellaSwag dataset as simple textfiles

#### Files

`hellaswag_val_full.txt`- All 10042 examples extracted from the official HellaSwag validation dataset: [hellaswag_val.jsonl](https://github.com/rowanz/hellaswag/blob/master/data/hellaswag_val.jsonl)

#### Preprocessing

All used data fields are preprocessed a bit better than the lm-evaluation-harness [hellaswag.py](https://github.com/EleutherAI/lm-evaluation-harness/blob/df3da98c5405deafd519c2ddca52bb7c3fe36bef/lm_eval/tasks/hellaswag.py#L62-L68)

#### Datafile layout:

`['??']` denotes a json field

The file contain 6 lines per task:

```
[activity_label'] + ": " + ['ctx']
['label']
['endings'][0]
['endings'][1]
['endings'][2]
['endings'][3]
```
