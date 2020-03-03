// disjoint-set data structure is represented on a single array
// each element points to parent element in the same set and forms tree,
// whose root points to itself and is the representative of the set

class DSU {
	private:
		int *data;
		int *size;
	public:
		DSU(int n) {
			data = new int[n];
			size = new int[n];
			for(int i = 0; i < n; i++) {
				data[i] = i;
				size[i] = 1;
			}
		}

		~DSU() {delete[] data; delete[] size;}

		// path compression without recursion
		int find(int i) {
			int parent;
			int back_to = -1;
			for(; i != (parent = data[i]); i = parent) {
				data[i] = back_to;
				back_to = i;
			}
			int root = i;
			while(back_to != -1) {
				i = back_to;
				back_to = data[i];
				data[i] = root;
			}
			return root;
		}

		// union by size
		// 'union' is reserved word
		void merge(int i, int j) {
			int ri = find(i), rj = find(j);
			if (ri == rj)
				return;
			if (size[ri] < size[rj]) {
				int t = ri;
				ri = rj;
				rj = t;
			}
			data[rj] = ri;
			size[ri] = size[ri] + size[rj];
		}

		int get_size(int i) {
			return size[find(i)];
		}
};
