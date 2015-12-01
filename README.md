## dev mode

```
mkdir make
cmake ../
nodemon -w ../src -w ../test -e c,cc,h -x 'rm testvoxels; car ; make ; ./testvoxels || true'
```
