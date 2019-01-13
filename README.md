# Improvement of the partially assembled genome with long readings

## Getting Started 
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
For building this project system needs to have instaled git and cmake, for unpacking downloaded data it is necessary to have unzip or similar program, for calculating overlaps system needs to have minimap2 which requires libz for building. 

Commands to setup prerequsites.
```
# install packages
sudo apt-get update
sudo apt-get install git
sudo apt-get install cmake
# needed to unzip downloaded data
sudo apt-get install unzip 
# needed to compile minimap2
sudo apt-get install libz-dev
```

### Installing
Guide for seting up the project. 

#### Setting up minimap2
Minimap2 is used to calculate overlaps between reads and reads, reads and contigs. Minimap is avaliable on [github](https://github.com/lh3/minimap2) and is described in 
> Li, H. (2018). Minimap2: pairwise alignment for nucleotide sequences.
> Bioinformatics. [doi:10.1093/bioinformatics/bty191][doi]

Commands to setup minimap2.
```
git clone https://github.com/lh3/minimap2.git
cd minimap2
make
cd ..
```

#### Build project source

```
# clone project from github and build
git clone https://github.com/domi385/bioinformatics.git
cd bioinformatics
mkdir build
cd build

#build project
cmake ..
make

# return to initial directory
cd ../../
```

#### Downloading example data
Example data is consisted of three datasets: BGrahamii (real), CJejuni (real), EColi (synthetic). Every dataset contains read sequences, contig sequences and reference sequence.
```
# data setup
mkdir resources
cd resources
# download data
wget -O data.zip https://www.dropbox.com/s/6uhqp3vtbx7usd9/Bioinformatika%20-%20scaffolding.zip?dl=1
unzip data.zip
rm data.zip
# rename directory
mv 'Bioinformatika - scaffolding' data
# inside data directory we have 3 directories 
# 'BGrahamii - real'  'CJejuni - real'  'EColi - synthetic'
# which contain initial data
# return to initial directory
cd ..
```

#### Calculate overlaps
BGrahamii - real
```
minimap2/minimap2 -x ava-pb 'resources/data/BGrahamii - real/BGrahamii - reads.fastq' 'resources/data/BGrahamii - real/BGrahamii - reads.fastq' > 'resources/data/BGrahamii - real/read_overlaps_bgra.paf'
minimap2/minimap2 -x ava-pb 'resources/data/BGrahamii - real/BGrahamii - reads.fastq' 'resources/data/BGrahamii - real/BGrahamii - contigs.fasta' > 'resources/data/BGrahamii - real/overlaps_bgra.paf'
```
CJejuni - real
```
minimap2/minimap2 -x ava-pb 'resources/data/CJejuni - real/CJejuni - reads.fastq' 'resources/data/CJejuni - real/CJejuni - reads.fastq' > 'resources/data/CJejuni - real/read_overlaps_cjej.paf'
minimap2/minimap2 -x ava-pb 'resources/data/CJejuni - real/CJejuni - reads.fastq' 'resources/data/CJejuni - real/CJejuni - contigs.fasta' > 'resources/data/CJejuni - real/overlaps_cjej.paf'
```
EColi - synthetic
```
minimap2/minimap2 -x ava-pb 'resources/data/EColi - synthetic/ecoli_test_reads.fasta' 'resources/data/EColi - synthetic/ecoli_test_reads.fasta' > 'resources/data/EColi - synthetic/read_overlaps_ecol.paf'
minimap2/minimap2 -x ava-pb 'resources/data/EColi - synthetic/ecoli_test_reads.fasta' 'resources/data/EColi - synthetic/ecoli_test_contigs.fasta' > 'resources/data/EColi - synthetic/overlaps_ecol.paf'
```

### Run examples
BGrahamii - real
```
bioinformatics/build/bioinformatics 'resources/data/BGrahamii - real/BGrahamii - contigs.fasta' 'resources/data/BGrahamii - real/BGrahamii - reads.fastq' 'resources/data/BGrahamii - real/overlaps_bgra.paf' 'resources/data/BGrahamii - real/read_overlaps_bgra.paf' results/result_bgrahamii.fasta
```
CJejuni - real
```
bioinformatics/build/bioinformatics 'resources/data/CJejuni - real/CJejuni - contigs.fasta' 'resources/data/CJejuni - real/CJejuni - reads.fastq' 'resources/data/CJejuni - real/overlaps_cjej.paf' 'resources/data/CJejuni - real/read_overlaps_cjej.paf' results/result_cjejuni.fasta
```
EColi - synthetic
```
bioinformatics/build/bioinformatics 'resources/data/EColi - synthetic/ecoli_test_contigs.fasta' 'resources/data/EColi - synthetic/ecoli_test_reads.fasta' 'resources/data/EColi - synthetic/overlaps_ecol.paf' 'resources/data/EColi - synthetic/read_overlaps_ecol.paf' results/result_cjejuni.fasta
```

## Faculty of Electrical Engineering and Computing, University of Zagreb
## Course: Bioinformatics https://www.fer.unizg.hr/en/course/bio
