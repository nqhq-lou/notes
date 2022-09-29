---
title: VSCode Jupyter 
tags: []
---

## Pylance error

- Pylance server crashed 5 times in the last 3 minutes. The server will not be restarted. See the ...
- see to Pylance issue: https://github.com/microsoft/pylance-release/issues/3126
	- `pylanceHandlesNotebooks`, `pylanceLspNotebooksEnabled`
	- Having the same issue. Setting `python.pylanceLspNotebooksEnabled` to `false` did resolve the issue for now, but then I start getting duplicate suggestions from IntelliSense in `.py` files after having opened and run a Jupyter notebook. Setting additionally `jupyter.pylanceHandlesNotebooks` to `false` gets rid of those duplicates as well and makes things usable for me again.