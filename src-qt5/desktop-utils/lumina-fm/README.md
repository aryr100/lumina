## File Manager for the Lumina Desktop

This is the "Insight" file manager from the Lumina desktop.

Key Features:
 * ZFS filesystem support for view/rollback of filesystem snapshots
 * Simple mediaplayer functionality (play files directly from a directory)
 * Simple slideshow functionality (browse through all image files in a directory)
 * Bookmark locations on the system for easy-access later.
 * Flexible Interface:
    * Open additional directories in new tabs
    * Each tab may have up to two directories open for side-by-side comparisons.
    * "Basic" or "Detailed" file information modes.
    * System-wide directories available in a tree-layout on the left side (may be collapsed as desired)

### Library Dependencies

1. Qt 5.2+ (specific modules listed below)
   * concurrent
   * core
   * gui
   * network
   * multimedia
   * multimediawidgets
   * svg
   * widgets
2. Other Libraries
   * libc

## Runtime Dependencies (optional)
* `lumina-archiver`: Allow for instant-extract of an archive into a new subfolder within the current directory
* `lumina-open`: Needed to allow "open-with" functionality for files
* `lumina-fileinfo`: Allows an option to view the properties of files

### Command Line Arguments

* Any paths listed after `lumina-fm` will open up new tabs of the browser
 * Example : `lumina-fm /usr /etc /bin`
* `-new-instance` will open Lumina-fm with a new browser window for the home directory
 * Example : `lumina-fm -new-instance`
* Paths can be used along with `-new-instance` to open a new browser to that path, mulitple arguments are allowed.  
 * Example : `lumina-fm -new-instance /usr /bin /etc`

 
