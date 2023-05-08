# bytepager
> Dynamic arena-like allocator for C

## Usage
```C
Bytepager pager = {0};
bytepager_init(&pager, (BytepagerConfig){
	// capacity of each page (in bytes)
    .page_capacity_bytes = 256,
	
	// a limit to how far we should reach for a new page
	// if the current page is full.
	.max_page_traversal = 32
});

// malloc
void* my_bytes = bytepager_malloc(&pager, 16);
// (Note): This also zero-initializes the memory for you.

// strdup
const char *copied = bytepager_strdup(&pager, "hello world");

// Clear and free all allocated memory.
// Use this if your intention is to re-use the same pager.
// This free's the memory you've allocated in all pages, but keeps the pages
// for later use.
bytepager_clear(&pager);

// Free everything.
bytepager_destroy(&pager);
```
