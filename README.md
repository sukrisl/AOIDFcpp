# AOIDFcpp Library

AOIDFcpp is an C++ framework library to work with ESP-IDF. The library provide an interface class for implementing active object design pattern and hierarchical state machine.

There are 3 main classes in the library:
- `AOidf` Active object interface class
- `AOSidf` Active object with state handling interface class
- `HSMidf` Hierarchical state machine interface class

## Adding component to your ESP-IDF project
To use the library you can manually clone the repo or add component as a submodule. Go to your project directory on the terminal and add repo as a git submodule:
```
git submodule add https://github.com/sukrisl/AOIDFcpp.git components/AOIDFcpp
```

Currently unstable and has very limited functionality, use at your own risk.
