# Action

## What is "action"

A repo-level irregular operation is referred to as "action" in _alex_.

Here are exmples of such irrugular operations:
- Create a new unit from template
- Generate a unittest coverage report
- Generate root file system image for cross build
- Manage release binaries (configure, build, enerate and verify)
- Gererate "progress report" for a specific task

## Hot to use it?

```
$ ./alex action-trigger [NAME] ...
```

Possible design
```
$ ./alex action [NAME] trigger ...
$ ./alex action [NAME] reset # Remove local data
$ ./alex action [NAME] descrbie
```

## Directory Layout

[NAME]/
  manifest <- [OPTIONAL]
  entry    <- [MANDATORY]

