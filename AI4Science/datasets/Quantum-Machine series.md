---
title: quantum-machine datasets
tags: [physics/solidstate/datasets, AI4Science/datasets]
---

- [official site for quantum-machine dataset](http://quantum-machine.org/datasets/)
	- include `QM7, QM7b, QM9, QM8`
	- include `MD trajs of small molecules, MD trajs of C7O2H10`
	- include `MD trajs of C7O2H10 with total energies and atomic forces`
	- include `SN2 reactions, Solvated protein fragments`
	- include `Molecules generated with G-SchNet`
	- include others



## QM7

- a subset of GDB-13, total 7165 molecules
- up to 23 atoms, heavy atoms, and `C, N, O, S`





## QM9
- [QM9 Charge Densities and Energies Calculated with VASP](https://data.dtu.dk/articles/dataset/QM9_Charge_Densities_and_Energies_Calculated_with_VASP/16794500)
	- calculate with ASE interface to VASP
```Python
Vasp(xc='PBE', istart=0, algo='Normal', icharg=2, nelm=180, ispin=1, nelmdl=6, isym=0, lcorr=True, potim=0.1, nelmin=5, kpts=[1,1,1], ismear=0, ediff=0.1E-05, sigma=0.1, nsw=0, ldiag=True, lreal='Auto', lwave=False, lcharg=True, encut=400)
```

- [a convenient dataset python module in DGL](https://docs.dgl.ai/generated/dgl.data.QM9Dataset.html#dgl.data.QM9Dataset)


- [paper with code on QM9](https://paperswithcode.com/dataset/qm9)
	- include papers run on QM9

- manual process to yaml files
```Python
import os
import numpy
import pyscf
import torch
import dgl
import ruamel.yaml as yaml
from pyscf import gto, lib, dft, scf
from pyscf.gto.mole import fromfile  # format_atom
from tqdm import tqdm
from pyscf.lib.parameters import BOHR


data_input_download_dir = '/nvme/louzekun/share_data/qm9/qm9_input_download'
data_input_dir = '/nvme/louzekun/share_data/qm9/qm9_input_pyscf'
data_input_download_list = [f for f in os.listdir(data_input_download_dir) if f.endswith('.xyz')]
print(f"{len(data_input_download_list)=}")

def format_atom(atom_str, unit='Ang'):
    """unit for input pos unit, output is in AU / Bohr unit"""
    if unit in ['Ang', 'ang', 'A', 'a']:
        unit = BOHR
    elif unit in ['Bohr', 'bohr', 'B', 'b', 'AU', 'au']:
        unit = 1.0
    atom_sep = [a.split('\t') for a in atom_str.split('\n')]
    atom_sep = [[a[0], a[1:4]] for a in atom_sep]
    atom = []
    for z, pos_raw in atom_sep:
        pos = []
        for i in pos_raw:
            if '*^' in i:  i = i.replace('*^', 'e')  # special exp mark makes error
            pos.append(float(i) / unit)
        atom.append([z, pos])
    return atom

for in_fname in tqdm(data_input_download_list):
    name = in_fname.split('_')[1].split('.')[0]
    out_fname = name + '.yaml'
    atom_str = fromfile(os.path.join(data_input_download_dir, in_fname), format='xyz')
    try:
        atom = format_atom(atom_str, unit='Ang')
    except (ValueError, SyntaxError):
        print(in_fname)
    data = {
        "name": name,
        "unit": "Bohr",  # au
        "atom": atom,
    }
    with open(os.path.join(data_input_dir, out_fname), 'w') as f:
        yaml.dump(data, f)
```





