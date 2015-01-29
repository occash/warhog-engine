# Version control in Warhog
Warhog supports version control integration with Git. 
Use this page to get more information.

## Setup version control
Version control is disabled for new project by default.
To enable Git follow this steps:

1. Go to project settings (Edit->Project settings) and set version control to enabled. 
2. Fill out settings, such as username, password etc.
3. Keep automatic add checked in order files to be automatically added to version control.
Otherwise you will have to add it manually.

## Using version control
You can now do most of version control operations right in editor.

### Resource view
You can right click resource in resource view to see actions.

| Action    | Description                 |
| ------ | -------------------------------- |
| Diff   | Diff against head |
| History | Commit history of this file |
| Reset | Reset file changes |
| Blame | See file authors |
| Commit | Add to pending commit |

Also now you will see overlay icons in resource view.

| Icon | Description |
| ---- | ----------- |
| Plus | New file |
| Question mark | Merge conflict |
| Lock | No changes (maybe better exclamation for changed) |

### Version control view

In this view you can control your branching, changes and commits.

---

Developers: [Version control](../dev/dvcs.md)