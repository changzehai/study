
/*************************
编译语句
gcc -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -I${ORACLE_HOME}/rdbms/public -I${ORACLE_HOME}/rdbms/demo -L${ORACLE_HOME}/lib -lclntsh  test1.c

OCI重定义数据类型：

typedef unsigned  char   ub1;
typedef signed  char   sb1;
typedef unsigned  short  ub2;
typedef signed  short  sb2;
typedef unsigned  int   ub4;
typedef signed  int   sb4;
typedef ub4      duword;
typedef sb4      dsword;
typedef dsword     dword;

*************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <oci.h>

/*user name and password*/
static text* username=(text *)"melco";
static text* password=(text *)"Orcl1234";
static text* oracle=(text *)"melco";

/* Define SQL statements to be used in program. */
static text* SQL=(text *)"select id, name  from student";

/*handle define*/
static OCIEnv    *p_env;          //OCI environment handle
static OCIError   *p_err;          //OCI error handle
static OCISvcCtx  *p_svc;          //OCI service context handel
static OCIServer  *p_ser;          //OCI server handle
static OCISession  *p_usr;          //OCI user session handle
static OCIStmt   *p_sql;          //OCI statement handle
static OCIDefine  *p_dfn = (OCIDefine *)NULL;   //OCI define handle
static OCIBind   *p_bnd = (OCIBind *)NULL;    //OCI bind handle


/*create OCI environment*/
int create_env()
{
 int swResult;   //Return value
 if(swResult = OCIEnvCreate(&p_env,OCI_DEFAULT,NULL,NULL,NULL,NULL,0,NULL))
  {
   printf("environment create error!\n\n");
   return -1;
  }
 else
  {
   printf("environment create success!\n\n");
   return 0;
  }
}

/*init handle*/
int init_handle()
{
 int swResult;
 if(swResult = OCIHandleAlloc(p_env,(dvoid *)&p_ser,OCI_HTYPE_SERVER,0,NULL)) //服务器句柄
  {
   printf("init server handle error!\n\n");
   return -1;
  }
 else
  {
   printf("init server handle success!\n\n");
  }

 if(swResult = OCIHandleAlloc(p_env,(dvoid *)&p_err,OCI_HTYPE_ERROR,0,NULL)) //错误句柄
  {
   printf("init error handle error!\n\n");
   return -1;
  }
 else
  {
   printf("init error handle success!\n\n");
  }
 if(swResult = OCIHandleAlloc(p_env,(dvoid *)&p_usr,OCI_HTYPE_SESSION,0,NULL)) //事务句柄
  {
   printf("init session handle error!\n\n");
   return -1;
  }
 else
  {
   printf("init session handle success!\n\n");
  }
 if(swResult = OCIHandleAlloc(p_env,(dvoid *)&p_svc,OCI_HTYPE_SVCCTX,0,NULL)) //上下文句柄
  {
   printf("init service context handle error!\n\n");
   return -1;
  }
 else
  {
   printf("init service context handel success!\n\n");
  }
 if(swResult = OCIHandleAlloc(p_env,(dvoid *)&p_sql,OCI_HTYPE_STMT,0,NULL))  //SQL语句句柄
  {
   printf("init statement handle error!\n\n");
   return -1;
  }
 else
  {
   printf("init statement handle success!\n\n");
  }
 return 0;
}

/*connect server*/
int conn_server()
{
 int swResult;
 if(swResult = OCILogon(p_env,p_err,&p_svc,(text *)username,strlen(username),(text *)password,strlen(password),(text *)oracle,strlen(oracle)))
  {
   printf("connect error!\n\n");
   return -1;
  }
 else
  printf("connect success!\n\n");
 return 0;
}

/*SQL statements*/
int oci_exec()
{
 int swResult;
 //准备SQL语句
 if(swResult = OCIStmtPrepare(p_sql,p_err,SQL,strlen(SQL),OCI_NTV_SYNTAX,OCI_DEFAULT))
  {
   printf("prepare SQL statements error!\n\n");
  }
 else
  {
   printf("prepare SQL statements success!\n\n");
  }

 //设置绑定变量
 int getId ;
 char getName[20];

 OCIBind  *p_bndp1 = NULL;
 OCIBind  *p_bndp2 = NULL;
 OCIDefine        *p_dfn1 = NULL;
 OCIDefine        *p_dfn2 = NULL; 


 if(swResult = OCIDefineByPos(p_sql,&p_dfn1,p_err,1,(dvoid *)&getId,(sb4)sizeof(getId),SQLT_INT,(dvoid *) 0, (ub2 *)0,(ub2 *)0,OCI_DEFAULT))
  {
   printf("Bind p1 error!\n\n");
   return -1;
  }
 else
  {
   printf("bind success!\n\n");
  }

 if(swResult = OCIDefineByPos(p_sql,&p_dfn2,p_err,2,&getName,(sb4)sizeof(getName),SQLT_STR, (dvoid *) 0, (ub2 *) 0, (ub2 *) 0, OCI_DEFAULT))
  {
   printf("Bind p2 error!\n\n");
   return -1;
  }
 else
  {
   printf("bind success!\n\n");
  }

/*
 //执行SQL statements
 if(swResult = OCIStmtExecute(p_svc,p_sql,p_err,1,0,NULL,NULL,OCI_DEFAULT))
  {
   printf("execute SQL statement error!\n\n");
   return -1;
  }
 else
  {
   printf("execute SQL statement success!\n\n");
  }
*/
  while(OCI_NO_DATA!= OCIStmtFetch(p_sql, p_err, (ub4)1, OCI_FETCH_NEXT, OCI_DEFAULT))
  {
      
   printf("id: %d, name: %s\n",getId, getName);

  }

 return 0;
}


/*quit server*/
void quit_server()
{
 OCILogoff(p_svc,p_err);
 printf("Quit success!\n");
}

/*free handle*/
void free_handle()
{
 OCIHandleFree(p_ser,OCI_HTYPE_SERVER);   //释放服务器句柄
 OCIHandleFree(p_err,OCI_HTYPE_ERROR);   //释放错误句柄
 OCIHandleFree(p_usr,OCI_HTYPE_SESSION);  //释放事务句柄
 OCIHandleFree(p_svc,OCI_HTYPE_SVCCTX);   //释放上下文句柄
 OCIHandleFree(p_sql,OCI_HTYPE_STMT);   //释放SQL语句句柄
}

int main()
{
 if(create_env() == -1)    //创建环境
  return -1;
 if(init_handle() == -1)    //初始化句柄
  return -1;
 if(conn_server() == -1)    //连接数据库
  return -1;
 if(oci_exec() == -1)
  return -1;
 quit_server();       //退出数据库
 free_handle();       //释放句柄
 return 0;
}

