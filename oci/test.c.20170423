#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <oci.h>


static OCIServer        *srvhp;
static OCISession       *p_session;
static OCIEnv           *p_env;
static OCIError         *p_err;
static OCISvcCtx        *p_svc;
static OCIStmt          *p_sql;
static OCIDefine        *p_dfn    = (OCIDefine *) 0;
static OCIBind          *p_bnd    = (OCIBind *) 0;

int  main()
{
	int             p_bvi;
	text           p_sli[10];


	int             rc;
	char            errbuf[100];
	int             errcode;

	rc = OCIInitialize((ub4) OCI_DEFAULT, (dvoid *)0,  /* Initialize OCI */
			(dvoid * (*)(dvoid *, size_t)) 0,
			(dvoid * (*)(dvoid *, dvoid *, size_t))0,
			(void (*)(dvoid *, dvoid *)) 0 );


	/* Initialize evironment */
	rc = OCIEnvInit( (OCIEnv **) &p_env, OCI_DEFAULT, (size_t) 0, (dvoid **) 0 );

	/* Initialize handles */
	rc = OCIHandleAlloc( (dvoid *) p_env, (dvoid **) &p_err, OCI_HTYPE_ERROR,
			(size_t) 0, (dvoid **) 0);
	rc = OCIHandleAlloc( (dvoid *) p_env, (dvoid **) &p_svc, OCI_HTYPE_SVCCTX,
			(size_t) 0, (dvoid **) 0);
	rc = OCIHandleAlloc( (dvoid *) p_env, (dvoid **) &p_session, OCI_HTYPE_SESSION,
			(size_t) 0, (dvoid **) 0);
	rc =OCIHandleAlloc( (dvoid *) p_env, (dvoid **) &srvhp, OCI_HTYPE_SERVER,
			(size_t) 0, (dvoid **) 0);
	printf("ddddd\n");
	/* Connect to database server */
	char usrname[20];
	char password[20];
	strcpy(usrname,"melco");
	strcpy(password,"Orcl1234");
	text *orcl="localhost";
	rc = OCIAttrSet((dvoid*)p_svc,(ub4)OCI_HTYPE_SVCCTX,(dvoid*)srvhp,(ub4)0,(ub4)OCI_ATTR_SERVER,p_err);
	if (rc != 0)
	{
		OCIErrorGet((dvoid *)p_err,1, (text *) NULL, &errcode, errbuf,sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("Error - %.*s\n", 512, errbuf);
		exit(8);
	}
	printf("ssss\n");
	rc = OCIAttrSet(p_session,OCI_HTYPE_SESSION,(text *)usrname,strlen(usrname),OCI_ATTR_USERNAME,p_err);
	if (rc != 0)
	{
		OCIErrorGet((dvoid *)p_err,1, (text *) NULL, &errcode, errbuf,sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("Error - %.*s\n", 512, errbuf);
		exit(8);
	}
	printf("111\n");
	rc = OCIAttrSet(p_session,OCI_HTYPE_SESSION,(text *)password,strlen(password),OCI_ATTR_PASSWORD,p_err);
	if (rc != 0)
	{
		OCIErrorGet((dvoid *)p_err,1, (text *) NULL, &errcode, errbuf,sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("Error - %.*s\n", 512, errbuf);
		exit(8);
	}
	printf("2222\n");

	rc = OCIServerAttach(srvhp,p_err,(text *)"localhost/melco",strlen("localhost/melco"),OCI_DEFAULT);
	if (rc != 0)
	{
		OCIErrorGet((dvoid *)p_err,1, (text *) NULL, &errcode, errbuf,sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("Error - %.*s\n", 512, errbuf);
		exit(8);
	}

	printf("3333\n");
	rc = OCISessionBegin(p_svc,p_err,p_session,OCI_CRED_RDBMS,OCI_DEFAULT);
	if (rc != 0)
	{
		OCIErrorGet((dvoid *)p_err,1, (text *) NULL, &errcode, errbuf,sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("Error - %.*s\n", 512, errbuf);
		exit(8);
	}
	printf("sssss\n"); 
	rc = OCIAttrSet(p_svc,OCI_HTYPE_SVCCTX,p_session,(ub4)0,OCI_ATTR_SESSION,p_err); 
	if (rc != 0)
	{
		OCIErrorGet((dvoid *)p_err,1, (text *) NULL, &errcode, errbuf,sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("Error - %.*s\n", 512, errbuf);
		exit(8);
	}  
	printf("tttt\n");
	/* Allocate and prepare SQL statement */
	rc = OCIHandleAlloc( (dvoid *) p_env, (dvoid **) &p_sql,
			OCI_HTYPE_STMT, (size_t) 0, (dvoid **) 0);
	if (rc != 0)
	{
		OCIErrorGet((dvoid *)p_err,1, (text *) NULL, &errcode, errbuf,sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("Error - %.*s\n", 512, errbuf);
		exit(8);
	}


	text *mySql = (text *) "SELECT name  FROM student"; 

	rc = OCIStmtPrepare(p_sql, p_err, mySql,(ub4) strlen(mySql), (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT);
	if (rc != 0)
	{
		OCIErrorGet((dvoid *)p_err,1, (text *) NULL, &errcode, errbuf,sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("Error - %.*s\n", 512, errbuf);
		exit(8);
	}


	rc = OCIDefineByPos(p_sql, &p_dfn, p_err, 1, (dvoid *) p_sli,
			(sb4)9, SQLT_CHR, (dvoid *) 0, (ub2 *)0,
			(ub2 *)0, OCI_DEFAULT);
	if (rc != 0)
	{
		OCIErrorGet((dvoid *)p_err,1, (text *) NULL, &errcode, errbuf,sizeof(errbuf), OCI_HTYPE_ERROR);
		printf("Error - %.*s\n", 512, errbuf);
		exit(8);
	}


	/* Execute the SQL statment */
	rc = OCIStmtExecute(p_svc, p_sql, p_err, (ub4)1,(ub4) 0, (OCISnapshot *) NULL, (OCISnapshot *) NULL,  
			(ub4) OCI_COMMIT_ON_SUCCESS);



	if(rc != OCI_NO_DATA)
	{
		printf("%s\n",p_sli);
	}
	else
	{
		printf("no data");
	}


	printf("over!\n");
	rc = OCIServerDetach(srvhp,p_err,OCI_DEFAULT);                         /* Disconnect */
	rc = OCIHandleFree((dvoid *) p_sql, OCI_HTYPE_STMT);    /* Free handles */
	rc = OCIHandleFree((dvoid *) p_svc, OCI_HTYPE_SVCCTX);
	rc = OCIHandleFree((dvoid *) p_err, OCI_HTYPE_ERROR);
	return;
}
