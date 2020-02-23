```
Pipeline p;

// Declare DAG
auto s = p.source<T>(...);
auto v1 = s | map(...) | filter(...);
auto v2 = v1 | map(...) | map(...);
auto v3 = v1 | map(...) | filter(...) | map(...);
union(v2, v3) | map(...) | filter(...) | to_console();

// NOTE There is no return value in the above example
//
// each map(...) or filter(...) returns a functor, and these functors will create a corresponding node 
// owned by p.
//

p.run(); // create a thread pool

p.feed(s) << 3;
p.feed(s) << 4;
```

### Design Questions

What happens if some node needs multiple inputs?
- This question lies at the core of stream processing framework such as GStreamer, NNStreamer, MediaPipe.
