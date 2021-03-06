/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* iFuseOper.h - Header for for iFuseOper.c */

#ifndef I_FUSE_OPER_H
#define I_FUSE_OPER_H

#include <sys/statvfs.h>
#include "rodsClient.h"
#include "rodsPath.h"
#include "iFuseLib.h"
#include "iFuseLib.Lock.h"

#define RECONNECT_IF_NECESSARY(s, c, o) \
	(s) = (o); \
	if (isReadMsgError (s)) { \
		ifuseReconnect (c); \
		(s) = (o); \
    }

#ifdef ENABLE_LAZY_UPLOAD

#define ALLOC_IFUSE_DESC_INDEX(f) \
    f->fh = (uint64_t)malloc(sizeof(uint64_t));

#define FREE_IFUSE_DESC_INDEX(f) \
    free((uint64_t*)(f->fh));

#define GET_IFUSE_DESC_INDEX(f) \
    (*((uint64_t*)(f->fh)))

#define SET_IFUSE_DESC_INDEX(f, i) \
    (*((uint64_t*)(f->fh))) = i;

#else

#define ALLOC_IFUSE_DESC_INDEX(f) \
    f->fh = 0;

#define FREE_IFUSE_DESC_INDEX(f) \
    f->fh = 0;

#define GET_IFUSE_DESC_INDEX(f) \
    f->fh

#define SET_IFUSE_DESC_INDEX(f, i) \
    f->fh = i;

#endif

#ifdef  __cplusplus
extern "C" {
#endif

int
_irodsGetattr (iFuseConn_t *iFuseConn, const char *path, struct stat *stbuf);
int irodsGetattr(const char *path, struct stat *stbuf);
int irodsReadlink(const char *path, char *buf, size_t size);
int irodsGetdir (const char *, char *, size_t);	/* Deprecated */
int irodsMknod(const char *path, mode_t mode, dev_t rdev);
int irodsMkdir(const char *path, mode_t mode);
int irodsUnlink(const char *path);
int irodsRmdir(const char *path);
int irodsSymlink(const char *from, const char *to);
int irodsRename(const char *from, const char *to);
int irodsLink(const char *from, const char *to);
int irodsChmod(const char *path, mode_t mode);
int irodsChown(const char *path, uid_t uid, gid_t gid);
int irodsTruncate(const char *path, off_t size);
int irodsFlush(const char *path, struct fuse_file_info *fi);
int
irodsUtimens (const char *path, const struct timespec ts[]);
int irodsOpen(const char *path, struct fuse_file_info *fi);
int irodsRead(const char *path, char *buf, size_t size, off_t offset, 
struct fuse_file_info *fi);
int irodsWrite(const char *path, const char *buf, size_t size, off_t offset, 
struct fuse_file_info *fi);
int irodsStatfs(const char *path, struct statvfs *stbuf);
int irodsRelease(const char *path, struct fuse_file_info *fi);
int irodsFsync (const char *path, int isdatasync, struct fuse_file_info *fi);
int irodsOpendir (const char *, struct fuse_file_info *);
int irodsReaddir(const char *path, void *buf, fuse_fill_dir_t filler, 
off_t offset, struct fuse_file_info *fi);

#ifdef  __cplusplus
}
#endif

#endif	/* I_FUSE_OPER_H */
