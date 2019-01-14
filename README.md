# Improvement of the partially assembled genome with long readings

Implementation of algorithm *[HERA - Highly efficient repeat assembly ][hera]* based on paper 
> H. Du i C. Liang. Assembly of chromosome-scale contigs by efficiently resolving repetitive sequences with long reads, 2018.  

Goal of the program is to try to connect contigs by using reads.

## Getting Started 

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.
Script containing all commands can also be found in the file [install.sh](install.sh)

### Prerequisites

For building this project system needs to have installed git and cmake, for unpacking downloaded data it is necessary to have unzip or similar program, for calculating overlaps system needs to have minimap2 which requires libz for building from source. 

Commands to setup prerequisites.
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

Guide for setting up the project. 

#### Setting up minimap2

Minimap2 is used to calculate overlaps between reads and reads, reads and contigs. Minimap2 is available on [GitHub](https://github.com/lh3/minimap2) and is described in 
> Li, H. (2018). Minimap2: pairwise alignment for nucleotide sequences.
> Bioinformatics. [doi:10.1093/bioinformatics/bty191][doi]

Commands to setup minimap2.
```
git clone https://github.com/lh3/minimap2.git
cd minimap2
make
cd ..
```

#### Build the project source

```
# clone project from GitHub and build
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

Example data contains three datasets: BGrahamii (real), CJejuni (real), E. Coli (synthetic). Every dataset contains read sequences, contig sequences and a reference sequence.
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
# return to the initial directory
cd ..
```

#### Calculate overlaps

Overlaps between reads and contigs or reads and reads are calculated using minimap2 and result is written in [PAF format][paf]. 
BGrahamii - real
```
# read read overlaps
minimap2/minimap2 -x ava-pb 'resources/data/BGrahamii - real/BGrahamii - reads.fastq' 'resources/data/BGrahamii - real/BGrahamii - reads.fastq' > 'resources/data/BGrahamii - real/read_overlaps_bgra.paf'
# read conting overlaps
minimap2/minimap2 -x ava-pb 'resources/data/BGrahamii - real/BGrahamii - reads.fastq' 'resources/data/BGrahamii - real/BGrahamii - contigs.fasta' > 'resources/data/BGrahamii - real/overlaps_bgra.paf'
```
CJejuni - real
```
# read read overlaps
minimap2/minimap2 -x ava-pb 'resources/data/CJejuni - real/CJejuni - reads.fastq' 'resources/data/CJejuni - real/CJejuni - reads.fastq' > 'resources/data/CJejuni - real/read_overlaps_cjej.paf'
# read conting overlaps
minimap2/minimap2 -x ava-pb 'resources/data/CJejuni - real/CJejuni - reads.fastq' 'resources/data/CJejuni - real/CJejuni - contigs.fasta' > 'resources/data/CJejuni - real/overlaps_cjej.paf'
```
EColi - synthetic
```
# read read overlaps
minimap2/minimap2 -x ava-pb 'resources/data/EColi - synthetic/ecoli_test_reads.fasta' 'resources/data/EColi - synthetic/ecoli_test_reads.fasta' > 'resources/data/EColi - synthetic/read_overlaps_ecol.paf'
# read conting overlaps
minimap2/minimap2 -x ava-pb 'resources/data/EColi - synthetic/ecoli_test_reads.fasta' 'resources/data/EColi - synthetic/ecoli_test_contigs.fasta' > 'resources/data/EColi - synthetic/overlaps_ecol.paf'
```

### Program parameters
Program can be run by using folowing command template:
```
bioinformatics contigs_path reads_path conting_read_overlaps_path read_read_overlaps_path result_path [si_min si_max n_monte_carlo n_max_node ci_max]
```
where parameters represent following:
* conting_path - path to file containing contig sequences in FASTA or FASTQ format
* reads_path - path to file containing read sequences in FASTA or FASTQ format
* conting_read_overlaps_path - path to file containing overlaps between conting sequences and read sequences in PAF format (generated with minimap2)
* read_read_overlaps_path - path to file containing overlaps between read sequences with themselves in PAF format (generated with minimap2)
* result_path - path to file where result should be written
* si_min - minimal sequence identity, overlaps with smaller SI will be filtered 
* si_max - maximal seuqnce identity, overlaps with SI bigger of equal to si_max will be filtered
* n_monte_carlo - number of Monte Carlo path generation iterations
* ci_max - maximal conflict index in connection graph, if the node has conflict index equal or greater than ci_max it won't be connected to other node

Program can accept 5 or 10 parameters where parameters given in [] are optional. Default values are si_min = 0.5, si_max = 1, n_monte_carlo = 1, n_max_node = 1000, ci_max = 0.7

Example of running program with default parameters:
```
bioinformatics/build/bioinformatics 'resources/data/BGrahamii - real/BGrahamii - contigs.fasta' 'resources/data/BGrahamii - real/BGrahamii - reads.fastq' 'resources/data/BGrahamii - real/overlaps_bgra.paf' 'resources/data/BGrahamii - real/read_overlaps_bgra.paf' results/result_bgrahamii.fasta
```

Example of running program with custom parameters:
```
bioinformatics/build/bioinformatics resources/data/CJejuni - real/CJejuni - contigs.fasta resources/data/CJejuni - real/CJejuni - reads.fastq resources/data/CJejuni - real/overlaps_cjej.paf resources/data/CJejuni - real/read_overlaps_cjej.paf results/result_cjejuni.fasta 0.5 1 10 1000 0.7
```

### Running examples

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

### Comparing results with reference
Resulting sequences can be compared to reference using [Genome Pair Rapid Dotter (Gepard)][gepard]. 

## Authors

* Authors: Domagoj Pluščec, Dunja Vesinger  
* Project made as part of Bioinformatics course at Faculty of Electrical Engineering and Computing, University of Zagreb  
* Academic year 2018/2019  
* Course link: https://www.fer.unizg.hr/en/course/bio  

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## List of References
> [H. Du i C. Liang. Assembly of chromosome-scale contigs by efficiently resolving repetitive sequences with long reads, 2018.][hera]  
> [H. Li. Minimap and miniasm: fast mapping and de novo assembly for noisy long sequences, 2017.][minimap2]  
> [H. Li. Minimap2: pairwise alignment for nucleotide sequences, 2018.][doi]  
> Mile Šikić i Mirjana Domazet-Lošo. Bioinformatika. 2013.  
> [Krumsiek J, Arnold R, Rattei T. Gepard: A rapid and sensitive tool for creating dotplots on genome scale. Bioinformatics 2007; 23(8): 1026-8. PMID: 17309896][gepard]

[doi]: https://doi.org/10.1093/bioinformatics/bty191
[paf]: https://github.com/lh3/miniasm/blob/master/PAF.md
[minimap2]: https://arxiv.org/abs/1512.01801
[hera]: https://www.biorxiv.org/content/early/2018/06/13/345983
[gepard]:http://cube.univie.ac.at/gepard