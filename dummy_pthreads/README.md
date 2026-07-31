This is a dummy version of pthreads, it isn't a real implementation.

This is only useful for projects that require pthreads, but don't actually make real use of it.

Some will use JUST the mutexes from pthreads and not actual threads, and this will allow them to be built.

These are useful for game ports that need these funcs to get them to compile, but they may not actually work.