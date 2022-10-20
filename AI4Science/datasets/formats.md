---
title: material datafile formats
tags: [AI4Science/dataset/formats]
---


### CIF
- The Crystallographic Information File (CIF for short) is a standard format, designed by the [International Union of Crystallography](http://www.iucr.org/resources/cif). As such, it is a very powerful and broadly used format.
	- CIF files for many compounds can be downloaded from the [American Mineralogist Crystal Structure Database (AMSD)](http://rruff.geo.arizona.edu/AMS/amcsd.php), or from the [Crystallography Open Database (COD)](http://www.crystallography.net/cod/), for instance.
- A file in the CIF format may contain the positions of atoms, as well as the symmetry group that the compound belongs to.
	- As such, it is a very peculiar format: all atoms positions are not written explicitly in a CIF file; they have to be constructed by applying the appropriate symmetry operations.


- to read in, use``
```python
from pymatgen.core.structure import Structure

def build_crystal(crystal_str, niggli=True, primitive=False):
    """Build crystal from cif string."""
    crystal = Structure.from_str(crystal_str, fmt='cif')
    if primitive:
        crystal = crystal.get_primitive_structure()
    if niggli:
        crystal = crystal.get_reduced_structure()
    canonical_crystal = Structure(
	    lattice=Lattice.from_parameters(
		    *crystal.lattice.parameters),
        species=crystal.species,
        coords=crystal.frac_coords,
        coords_are_cartesian=False,
    )
    # match is gaurantteed because cif only uses lattice params & frac_coords
    # assert canonical_crystal.matches(crystal)
    return canonical_crystal
```
