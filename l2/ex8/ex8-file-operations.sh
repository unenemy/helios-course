#!/bin/bash
while true; do
  read -p "Enter file operation (copy, remove, rename or link): " operation
  case $operation in
    "copy")
      read -p "Enter file to copy: " file
      read -p "Enter file to paste: " new_file
      if cp $file $new_file
      then
        echo "File $file copied to $new_file"
      fi
      ;;
    "remove")
      read -p "Enter file to remove: " file
      if rm $file
      then
        echo "File $file removed"
      fi
      ;;
    "rename")
      read -p "Enter file to rename: " file
      read -p "Enter new name: " new_file
      if mv $file $new_file
      then
        echo "File $file renamed to $new_file"
      fi
      ;;
    "link")
      read -p "Enter file to link: " file
      read -p "Enter link name: " link
      if ln -s $file $link
      then
        echo "Link $file_new linked to $file"
      fi
      ;;
    *)
      echo "wrong command try again"
      ;;
  esac
done
