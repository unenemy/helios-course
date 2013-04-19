#!/bin/bash
grps=`groups | sed 's/ /|/g'`
echo Files permited to read, write and execute for user $USER:
# match for                                   -- anybody ---    ---------- group access ---------------     ----- user access --------------
ls -l | awk -v grps=$grps -v user=$USER '{ if (($1~/.*rwx$/) || (($4~/'^"$grps"$'/) && ($1~/.*rwx...$/)) || (($3 == user) && ($1~/^.rwx.*/))) print $9 }'
