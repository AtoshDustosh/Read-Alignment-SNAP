# Read alignment


This project is one of the course labs of Bio-info. The lab is to realize the alignment tool using specific algorithms from Bowtie, BWA, SNAP, or any other practical algorithms. 

At first I planned to chose Bowtie, because it's simple and easy to implement. But later I considered it to be too simple for this project, so I decided to implement SNAP. 

During the implementation stage, I spent a long time trying to figure out how the algorithm works. Then it took me about several weeks to build the necessary parts of the program, including some compressing structure and structures for index. 

Final results:
	the program works, but there is memroy leak, and it will take tons of memory to run the program if the reference genome is too big. (about 1GB RAM for a 5MB ref)

	Not very good results. But still, there are many useful implementations in this project, especially the hashTable, AVL-tree and binaryCompressing of ref.