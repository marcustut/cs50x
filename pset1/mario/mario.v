import os { input }

fn main() {
	mut height := -1
	for height <= 0 || height > 8 {
		height = input('Height: ').int()
	}

	for i in 1 .. height + 1 {
		for _ in 0 .. height - i {
			print(' ')
		}

		for _ in 0 .. i {
			print('#')
		}

		print('  ')

		for _ in 0 .. i {
			print('#')
		}

		print('\n')
	}
}
