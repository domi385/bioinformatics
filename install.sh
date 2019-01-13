# install packages
sudo apt-get update
sudo apt-get install git
sudo apt-get install cmake
# needed to unzip downloaded data
sudo apt-get install unzip 
#needed to compile minimap2
sudo apt-get install libz-dev

# clone minimap from github 
git clone https://github.com/lh3/minimap2.git
cd minimap2
make
cd ..

# initial data setup
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

# calculating data overlaps
#BGrahamii - real
minimap2/minimap2 -x ava-pb 'resources/data/BGrahamii - real/BGrahamii - reads.fastq' 'resources/data/BGrahamii - real/BGrahamii - reads.fastq' > 'resources/data/BGrahamii - real/read_overlaps_bgra.paf'
minimap2/minimap2 -x ava-pb 'resources/data/BGrahamii - real/BGrahamii - reads.fastq' 'resources/data/BGrahamii - real/BGrahamii - contigs.fasta' > 'resources/data/BGrahamii - real/overlaps_bgra.paf'
#CJejuni - real
minimap2/minimap2 -x ava-pb 'resources/data/CJejuni - real/CJejuni - reads.fastq' 'resources/data/CJejuni - real/CJejuni - reads.fastq' > 'resources/data/CJejuni - real/read_overlaps_cjej.paf'
minimap2/minimap2 -x ava-pb 'resources/data/CJejuni - real/CJejuni - reads.fastq' 'resources/data/CJejuni - real/CJejuni - contigs.fasta' > 'resources/data/CJejuni - real/overlaps_cjej.paf'
#EColi - synthetic
minimap2/minimap2 -x ava-pb 'resources/data/EColi - synthetic/ecoli_test_reads.fasta' 'resources/data/EColi - synthetic/ecoli_test_reads.fasta' > 'resources/data/EColi - synthetic/read_overlaps_ecol.paf'
minimap2/minimap2 -x ava-pb 'resources/data/EColi - synthetic/ecoli_test_reads.fasta' 'resources/data/EColi - synthetic/ecoli_test_contigs.fasta' > 'resources/data/EColi - synthetic/overlaps_ecol.paf'


# clone project from github and build
git clone https://github.com/domi385/bioinformatics.git
cd bioinformatics
mkdir build
cd build
cmake ..
make
# return to initial directory
cd ../../

# run program
mkdir results
bioinformatics/build/bioinformatics 'resources/data/CJejuni - real/CJejuni - contigs.fasta' 'resources/data/CJejuni - real/CJejuni - reads.fastq' 'resources/data/CJejuni - real/overlaps_cjej.paf' 'resources/data/CJejuni - real/read_overlaps_cjej.paf' results/result_cjejuni.fasta

bioinformatics/build/bioinformatics 'resources/data/BGrahamii - real/BGrahamii - contigs.fasta' 'resources/data/BGrahamii - real/BGrahamii - reads.fastq' 'resources/data/BGrahamii - real/overlaps_bgra.paf' 'resources/data/BGrahamii - real/read_overlaps_bgra.paf' results/result_bgrahamii.fasta

bioinformatics/build/bioinformatics 'resources/data/EColi - synthetic/ecoli_test_contigs.fasta' 'resources/data/EColi - synthetic/ecoli_test_reads.fasta' 'resources/data/EColi - synthetic/overlaps_ecol.paf' 'resources/data/EColi - synthetic/read_overlaps_ecol.paf' results/result_cjejuni.fasta


