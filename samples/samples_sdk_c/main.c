// +-------------------------------------------------------------------------
// | Copyright (C) 2017 Yunify, Inc.
// +-------------------------------------------------------------------------
// | Licensed under the Apache License, Version 2.0 (the "License");
// | you may not use this work except in compliance with the License.
// | You may obtain a copy of the License in the LICENSE file, or at:
// |
// | http://www.apache.org/licenses/LICENSE-2.0
// |
// | Unless required by applicable law or agreed to in writing, software
// | distributed under the License is distributed on an "AS IS" BASIS,
// | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// | See the License for the specific language governing permissions and
// | limitations under the License.
// +-------------------------------------------------------------------------

// +-------------------------------------------------------------------------
// | This Example shows how to use the API interface.
// | For more information, please refer to URL :
// | 
// | You should configure the following environment variables to ensure the 
// | smooth execution of the program:
// | QINGSTOR_CONFIG_PATH : QingStor config file path
// | QINGSTOR_BUCKET_NAME : QingStor bucket name
// | QINGSTOR_ZONE_NAME : QingStor zone name
// +-------------------------------------------------------------------------
#include <stdio.h>
#include "qingstor/service_with_c_style/QsList.h"
#include "qingstor/service_with_c_style/QingStorCStyle.h"

void ShowHow2Do_InitiateMultipartUpload(qs_context_handle context_hdl, char* objectkey, char** uploadID)
{
    if(context_hdl.pQsBucket == NULL || context_hdl.pQsService == NULL){
        return;
    }

    qs_initiate_multipart_upload_input_t input;
    qs_initiate_multipart_upload_output_t output;
    init_initiate_multipart_upload_input (&input);

    QsError err = qs_initiate_multipart_upload(objectkey, &input, &output, context_hdl);
    if (QS_ERR_NO_ERROR == err && output.response_code == 200)
    {
       printf("uploadID is %s\n",output.upload_id);
	   *uploadID = (char*)malloc(strlen(output.upload_id) + 1);
	   memset((*uploadID), 0, strlen(output.upload_id) + 1);
	   memcpy((*uploadID), output.upload_id, strlen(output.upload_id));
    }

	release_initiate_multipart_upload_output(&output);

    printf("Initiate Multipart Upload is finished\n");
    return;
}

void ShowHow2Do_UploadMultipart(qs_context_handle context_hdl, char* objectkey, char* uploadID ,int partNumber)
{
    if(context_hdl.pQsBucket == NULL || context_hdl.pQsService == NULL){
        return;
    }

    qs_upload_multipart_input_t input;
    qs_upload_multipart_output_t output;
    init_upload_multipart_input (&input);

	long length = 5 * 1024 * 1024; //fiveMbSize
	int part_number = partNumber;
	input.bodybuf = (char *)malloc(length);
	memset(input.bodybuf, 0, length);
	input.bufLength = &length;
	input.content_length = &length;
	input.part_number = &part_number;
    input.upload_id = uploadID;

    QsError err = qs_upload_multipart (objectkey, &input, &output, context_hdl);
    if (QS_ERR_NO_ERROR == err)
    {
        // print sth
        printf("Part %d is finished.\n",partNumber);
    }
   
    // when api finish, you should release resource.
    if(input.bodybuf)
    {
        free(input.bodybuf);
        input.bodybuf = NULL;
    }
    
	release_upload_multipart_output(&output);

    return;
}

void ShowHow2Do_CompleteMultipartUpload(qs_context_handle context_hdl, char* objectkey, char* uploadID, qs_list_t * objectParts)
{
	if (context_hdl.pQsBucket == NULL || context_hdl.pQsService == NULL){
		return;
	}

	qs_complete_multipart_upload_input_t input;
	qs_complete_multipart_upload_output_t output;
	init_complete_multipart_upload_input(&input);

	input.object_parts = objectParts;
	input.upload_id = uploadID;

	QsError err = qs_complete_multipart_upload(objectkey, &input, &output, context_hdl);
	if (QS_ERR_NO_REQUIRED_PARAMETER == err)
	{
		printf("%s\n", "The input object lacks some of the parameters that must be filled in.");
	}
	else if (QS_ERR_UNEXCEPTED_RESPONSE == err)
	{
		int responsecode = output.response_code;
        printf("the ListObject responsecode is %d\n", responsecode);
	}

	release_complete_multipart_upload_output(&output);

	return;
}

void ShowHow2Do_ListObjects(qs_context_handle context_hdl)
{
    if(context_hdl.pQsBucket == NULL || context_hdl.pQsService == NULL){
        return;
    }

    // List Objects
    qs_list_objects_input_t input;
    qs_list_objects_output_t output;
    init_list_objects_input(&input);
    // if you want limit the maximum number of object in response, you can set "Limit" paramter. 
    // the default value is 200, maximum allowable set 1000
    int limitNum = 100;
    input.limit = &limitNum;// 

    QsError err = qs_list_objects(&input, &output, context_hdl);


    if(QS_ERR_NO_ERROR == err)
    {
        qs_list_t *keys = output.keys;
        int count = 0;
        qs_key_item_t *pos;
        qs_list_for_each_entry(qs_key_item_t, pos, keys)
        {
            count++;
        }
        printf("Got %d objects\n" ,count);
    }   
    
    if (QS_ERR_UNEXCEPTED_RESPONSE == err )
    {
        printf("request_id = %s , with detail message : %s\n" , output.error_info.request_id, output.error_info.message);
    }

    release_list_objects_output(&output);


    return;
}


void ShowHow2Do_MultipartUploadObject(qs_context_handle context_hdl, char* objectkey)
{
    if(context_hdl.pQsBucket == NULL || context_hdl.pQsService == NULL){
        return;
    }

    char* uploadID = NULL;

    ShowHow2Do_InitiateMultipartUpload(context_hdl , objectkey , &uploadID);

    ShowHow2Do_UploadMultipart(context_hdl, objectkey, uploadID ,1);

    ShowHow2Do_UploadMultipart(context_hdl, objectkey, uploadID ,2);

	qs_list_t object_parts_list;
	qs_list_init(&object_parts_list);
	qs_object_part_item_t object_parts_item_1, object_parts_item_2;
	qs_object_part_t object_parts_1, object_parts_2;
	init_object_part(&object_parts_1);
	init_object_part(&object_parts_2);

	int part_number_1 = 1;
	int part_number_2 = 2;
	object_parts_1.part_number = &part_number_1;
	object_parts_2.part_number = &part_number_2;
	object_parts_item_1.content = &object_parts_1;
	object_parts_item_2.content = &object_parts_2;
	qs_list_append(&object_parts_item_1.node, &object_parts_list);
	qs_list_append(&object_parts_item_2.node, &object_parts_list);

	ShowHow2Do_CompleteMultipartUpload(context_hdl, objectkey, uploadID, &object_parts_list);

    if(uploadID)
    {
        free(uploadID);
    }

    return;
}


void ShowHow2Do_GetObject(qs_context_handle context_hdl, char* objectkey)
{
    if(context_hdl.pQsBucket == NULL || context_hdl.pQsService == NULL){
        return;
    }

    qs_get_object_input_t input;
    qs_get_object_output_t output;
    init_get_object_input (&input);

	QsError err = qs_get_object(objectkey, &input, &output, context_hdl);
    if(QS_ERR_NO_REQUIRED_PARAMETER == err)
    {
        printf("%s\n" , "The input object lacks some of the parameters that must be filled in.");
    }
    
    if (QS_ERR_UNEXCEPTED_RESPONSE == err )
    {
        printf("request_id = %s , with detail message : %s\n" , output.error_info.request_id, output.error_info.message);
    }

	if (output.bodybuf)
	{
		printf("The length of object is : %ld\n", *output.bufLength);
	}

	release_get_object_output(&output);

    return;
}


void ShowHow2Do_DeleteObject(qs_context_handle context_hdl, char* objectkey)
{
    if(context_hdl.pQsBucket == NULL || context_hdl.pQsService == NULL){
        return;
    }

    qs_delete_object_input_t input;
    qs_delete_object_output_t output;
    init_delete_object_input (&input);

	QsError err = qs_delete_object(objectkey, &input, &output, context_hdl);
    if(QS_ERR_NO_REQUIRED_PARAMETER == err)
    {
        printf("%s\n" , "The input object lacks some of the parameters that must be filled in.");
    }

    if (QS_ERR_UNEXCEPTED_RESPONSE == err )
    {
        printf("request_id = %s , with detail message : %s\n" , output.error_info.request_id, output.error_info.message);
    }

    printf("object(%s) has been deleted.\n" , objectkey);

    release_delete_object_output(&output);
    
    return;
}

int main()
{
    // Read necessary information from envirox  nment variables.
    char *strConfigPath ="/etc/qingstor/config.yaml";// getenv("QINGSTOR_CONFIG_PATH");
    char *strBucketName = "huang-stor";//getenv("QINGSTOR_BUCKET_NAME");
    char *strZone = "zone";//getenv("QINGSTOR_ZONE_NAME");
    if(!strConfigPath || !strBucketName || !strZone)
    {
        printf("Envionment variables are missing : QINGSTOR_CONFIG_PATH or QINGSTOR_BUCKET_NAME or QINGSTOR_ZONE_NAME.\n");
        return 1;
    }
    printf("QINGSTOR_CONFIG_PATH: %s.\n",strConfigPath);
    printf("QINGSTOR_BUCKET_NAME: %s.\n",strBucketName);
    printf("QINGSTOR_ZONE_NAME: %s.\n",strZone);

	char* objectkey = "QingStor_SDK_Test_File";

	qs_init_sdk("/tmp/", Debug, 1);

	// Global initialization only needs to be initialized once
    qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);
    // Valid log levels are "none","debug", "info", "warn", "error", and "fatal".(default value is "None")

    ShowHow2Do_ListObjects(context_hdl);  
    
    ShowHow2Do_MultipartUploadObject(context_hdl, objectkey);

    ShowHow2Do_GetObject(context_hdl, objectkey);

    ShowHow2Do_DeleteObject(context_hdl, objectkey);

    qs_release_service(context_hdl);

	qs_shutdown_sdk(1);

    return 0;
}






