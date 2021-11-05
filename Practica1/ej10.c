
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pwd.h>



int main(){

	uid_t uid = getuid();
	
	struct passwd pswd;
	
	pswd = *getpwuid(uid);
	
	printf("REAL UID: %d\nEFECTIVE UID: %d\nUsername: %s\nDesc: %s\nHome: %s\n", 
		uid, geteuid(), pswd.pw_name, pswd.pw_gecos, pswd.pw_dir);
	return 0;

}