# Version control

## Resource view
* Context menu in resource view (see [Version Control](../editor/dvcs.md))
* Icon overlays in resource view (see [Version Control](../editor/dvcs.md))

## Version control view

Use [libgit2](https://libgit2.github.com/) to develop version control functionality.

### Branches tab

![Branches](img/editor/dcvs_branches.png)

*Context menu* for branch list

| Action | Description |
| ------ | ----------- |
| Switch | Make selected branch current |
| Publish/Unpublish | Depends on weather the branch has tracking link |
| History | Branch commit history |
| Delete | Delete selected branch |

Include *New branch* and *Merge* in context menu?

*New branch dialog*

![New branch command](img/editor/dcvs_new_dialog.png)

*Merge dialog*

![Merge command](img/editor/dcvs_merge_dialog.png)

### Changes tab

![Branches](img/editor/dcvs_changes.png)

Commit button menu

* Commit
* Commit & push
* Commit & sync

*Context menu* for file list

For included/excluded

* History
* Diff ("Compare" is better?)
* Annotate
* Exclude/Include
* Reset

For untracked

* Add
* Delete
* Ignore file
* Ignore type (texture)

### Unsynced tab

![Branches](img/editor/dcvs_unsynced.png)

## Compare view

* Use [dtl-cpp](https://code.google.com/p/dtl-cpp/) to develop text diff.
* Use [github](https://github.com/blog/1633-3d-file-diffs) as reference for 3d model diff.
* Use [Perforce](http://www.perforce.com/resources/tutorials/using-image-diff-tool) as reference for image diff.

## History view

Just a list of commits

Context menu for commit

* Details - open dialog similar to changes tab
* Revert - create revert commit