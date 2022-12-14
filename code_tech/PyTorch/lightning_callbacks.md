---
title: callbacks by pytorch_lightning
tags: [pytorch/lightning]
---


## callbacks

```Python
from pytorch_lightning.callbacks.callback import Callback
from pytorch_lightning.callbacks.checkpoint import Checkpoint
from pytorch_lightning.callbacks.device_stats_monitor import DeviceStatsMonitor
from pytorch_lightning.callbacks.early_stopping import EarlyStopping
from pytorch_lightning.callbacks.finetuning import BackboneFinetuning, BaseFinetuning
from pytorch_lightning.callbacks.gradient_accumulation_scheduler import GradientAccumulationScheduler
from pytorch_lightning.callbacks.lambda_function import LambdaCallback
from pytorch_lightning.callbacks.lr_monitor import LearningRateMonitor
from pytorch_lightning.callbacks.model_checkpoint import ModelCheckpoint
from pytorch_lightning.callbacks.model_summary import ModelSummary
from pytorch_lightning.callbacks.prediction_writer import BasePredictionWriter
from pytorch_lightning.callbacks.progress import ProgressBarBase, RichProgressBar, TQDMProgressBar
from pytorch_lightning.callbacks.pruning import ModelPruning
from pytorch_lightning.callbacks.quantization import QuantizationAwareTraining
from pytorch_lightning.callbacks.rich_model_summary import RichModelSummary
from pytorch_lightning.callbacks.stochastic_weight_avg import StochasticWeightAveraging
from pytorch_lightning.callbacks.timer import Timer
```