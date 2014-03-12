/*
 * @author Mário Soares
 * @contributors Jefferson González
 * 
 * @license 
 * This file is part of wxPHP check the LICENSE file for information.
 * 
 * @description
 * File that holds the functions code of the wxWidgets extension
 * 
 * @note
 * Some parts of this file are auto-generated by the wxPHP source maker
*/

#include "php_wxwidgets.h"
#include "functions.h"

#ifdef __WXMAC__
/* Header for process type transformation functions */
#include <ApplicationServices/ApplicationServices.h>
#endif

<?php print $header_files ?>

/**
 * Forwards some or all of the function parameters to PHP's sprintf.
 * Returns a formatted string or NULL.
 */
zval * wxphp_sprintf(INTERNAL_FUNCTION_PARAMETERS, int offset = 0)
{
	int		argc = ZEND_NUM_ARGS();
	zval	***argv;
	zval	funcName, *string, *retVal = NULL;
	
	if (argc < 1) {
		WRONG_PARAM_COUNT_WITH_RETVAL(NULL);
	}
	
	argv = (zval ***) safe_emalloc(argc, sizeof(zval **), 0);
	
	if (zend_get_parameters_array_ex(argc, argv) == FAILURE) {
		efree(argv);
		WRONG_PARAM_COUNT_WITH_RETVAL(NULL);
	}
		
	ZVAL_STRINGL(&funcName, "sprintf", sizeof("sprintf") - 1, 0);

	if (call_user_function_ex(EG(function_table), NULL, &funcName, &string,
		argc - offset, argv + offset, 0, NULL TSRMLS_CC) == SUCCESS)
	{
		if (Z_TYPE_P(string) == IS_STRING)
			retVal = string;
		else
			zval_ptr_dtor(&string);
	}
	
	efree(argv);
	
	return retVal;
}

/**
 * Predefined handcoded set of functions
 */
 
/* {{{ proto int wxExecute(string command)
   Executes another program in Unix or Windows. */
PHP_FUNCTION(php_wxExecute)
{
	char* _argStr0;
	int _argStr0_len;

    long flags = 0;
    zval* z_process = 0;
    wxProcess* process;

    long ret;
    
	char parse_parameters[] = "s|lO";
    
	if(
        zend_parse_parameters_ex(
            ZEND_PARSE_PARAMS_QUIET, 
            ZEND_NUM_ARGS() TSRMLS_CC, 
            parse_parameters, 
            &_argStr0, &_argStr0_len, 
            &flags, &z_process, php_wxProcess_entry 
        ) == SUCCESS
    )
	{

        switch(ZEND_NUM_ARGS())
        {
            case 1:
                ret = wxExecute(wxString(_argStr0, wxConvUTF8));
                RETURN_LONG(ret)
                break;

            case 2:
                ret = wxExecute(wxString(_argStr0, wxConvUTF8), (int) flags);
                RETURN_LONG(ret)
                break;

            case 3:
                process = (wxProcess*) ((zo_wxProcess*) zend_object_store_get_object(z_process TSRMLS_CC))->native_object;
                ret = wxExecute(wxString(_argStr0, wxConvUTF8), (int) flags, process);
                RETURN_LONG(ret)
                break;

            default:
                WRONG_PARAM_COUNT;
        }
	}

    RETURN_LONG((long) 0)
}
/* }}} */

/* {{{ proto int wxEntry()
   This function initializes wxWidgets in a platform-dependent way. */
PHP_FUNCTION(php_wxEntry)
{
	#ifdef __WXMAC__
    /* In order to correctly receive keyboard input we need to explicitly
     * tell mac to convert this console process to a gui process.
     *
     * Solution found at: 
     * http://stackoverflow.com/questions/4341098/wxwidgets-commandline-gui-hybrid-application-fails-to-get-dialog-input
     */
    ProcessSerialNumber PSN;
    GetCurrentProcess(&PSN);
    TransformProcessType(&PSN,kProcessTransformToForegroundApplication);
    #endif

	int argc = 1;
	char application_name[] = "wxPHP";
	char *argv[2] = { application_name, NULL };
	
	RETVAL_LONG(wxEntry(argc, argv));
}
/* }}} */

/* {{{ proto object wxC2D(object wxwidgets_object_constant)
   Converts a wxWidgets constant object to dynamic in order to be able to access its methods like wxC2D(wxNORMAL_FONT)->GetPointSize(). */
PHP_FUNCTION(php_wxC2D)
{	
	zval* constant_object = 0;
	
	char parse_parameters[] = "z";
    
    if(ZEND_NUM_ARGS() == 1)
    {
		if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, parse_parameters, &constant_object ) == SUCCESS)
		{	
			*return_value = *constant_object;
			zval_add_ref(&constant_object);
			return;
		}
	}
	
	zend_error(E_ERROR, "Ivalid count or type of parameters for wxC2D(), you should pass a constant object to transform to dynamic\n");
}
/* }}} */

/* {{{ proto void wxLogError(string formatString, ...)
   The function to use for error messages, i.e. the messages that must be shown to the user. The default processing is to pop up a message box to inform the user about it. */
PHP_FUNCTION(php_wxLogError)
{
	zval *message;
	
	if (message = wxphp_sprintf(INTERNAL_FUNCTION_PARAM_PASSTHRU))
	{
		wxLogError(Z_STRVAL_P(message));
		zval_ptr_dtor(&message);
	}
}
/* }}} */

/* {{{ proto void wxLogFatalError(string formatString, ...)
   Like wxLogError(), but also terminates the program with the exit code 3. */
PHP_FUNCTION(php_wxLogFatalError)
{
	zval *message;
	
	if (message = wxphp_sprintf(INTERNAL_FUNCTION_PARAM_PASSTHRU))
	{
		wxLogFatalError(Z_STRVAL_P(message));
		zval_ptr_dtor(&message);
	}
}
/* }}} */

/* {{{ proto void wxLogGeneric(int level, string formatString, ...)
   Logs a message with the given wxLogLevel. */
PHP_FUNCTION(php_wxLogGeneric)
{
	char	parse[] = "l";
	long 	logLevel;
	zval	*message;
	
	if (ZEND_NUM_ARGS() < 2) {
		WRONG_PARAM_COUNT;
	}
	
	if (zend_parse_parameters(1 TSRMLS_CC, parse, &logLevel) == SUCCESS)
	{
		if (message = wxphp_sprintf(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1))
		{
			wxLogGeneric(logLevel, Z_STRVAL_P(message));
			zval_ptr_dtor(&message);
		}
	}
}
/* }}} */

/* {{{ proto void wxLogMessage(string formatString, ...)
   For all normal, informational messages. */
PHP_FUNCTION(php_wxLogMessage)
{
	zval *message;
	
	if (message = wxphp_sprintf(INTERNAL_FUNCTION_PARAM_PASSTHRU))
	{
		wxLogMessage(Z_STRVAL_P(message));
		zval_ptr_dtor(&message);
	}
}
/* }}} */

/* {{{ proto void wxLogStatus([wxFrame frame,] string formatString, ...)
   Messages logged by this function will appear in the statusbar of the frame or of the top level application window. */
PHP_FUNCTION(php_wxLogStatus)
{
	char		parse[] = "O";
	wxFrame 	*frame = NULL;
	zval		*zFrame;
	zval		*message;
	
	if (ZEND_NUM_ARGS() < 1) {
		WRONG_PARAM_COUNT;
	}
	
	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, 1 TSRMLS_CC,
		parse, &zFrame, php_wxFrame_entry) == SUCCESS)
	{
		// Called with wxFrame as first parameter
	
		frame = (wxFrame*)
			((zo_wxFrame*) zend_object_store_get_object(zFrame TSRMLS_CC))->native_object;

		message = wxphp_sprintf(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
	}
	else
		message = wxphp_sprintf(INTERNAL_FUNCTION_PARAM_PASSTHRU);

	if (message)
	{
		if (frame)
			wxLogStatus(frame, Z_STRVAL_P(message));
		else
			wxLogStatus(Z_STRVAL_P(message));
	
		zval_ptr_dtor(&message);
	}
}
/* }}} */

/* {{{ proto void wxLogSysError(string formatString, ...)
   Logs the specified message text as well as the last system error code (errno or GetLastError() depending on the platform) and the corresponding error message. */
PHP_FUNCTION(php_wxLogSysError)
{
	zval *message;
	
	if (message = wxphp_sprintf(INTERNAL_FUNCTION_PARAM_PASSTHRU))
	{
		wxLogSysError(Z_STRVAL_P(message));
		zval_ptr_dtor(&message);
	}
}
/* }}} */

/* {{{ proto void wxLogVerbose(string formatString, ...)
   For verbose output. Normally, it is suppressed, but might be activated if the user wishes to know more details about the program progress (another, but possibly confusing name for the same function could be wxLogInfo). */
PHP_FUNCTION(php_wxLogVerbose)
{
	zval *message;
	
	if (message = wxphp_sprintf(INTERNAL_FUNCTION_PARAM_PASSTHRU))
	{
		wxLogVerbose(Z_STRVAL_P(message));
		zval_ptr_dtor(&message);
	}
}
/* }}} */

/* {{{ proto void wxLogWarning(string formatString, ...)
   For warnings - they are also normally shown to the user, but don't interrupt the program work. */
PHP_FUNCTION(php_wxLogWarning)
{
	zval *message;
	
	if (message = wxphp_sprintf(INTERNAL_FUNCTION_PARAM_PASSTHRU))
	{
		wxLogWarning(Z_STRVAL_P(message));
		zval_ptr_dtor(&message);
	}
}
/* }}} */

/**
 * Space reserved for autogenerated functions
 */
 
<?php print $functions ?>
