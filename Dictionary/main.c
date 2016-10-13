/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2016 Jean-David Gadina - www-xs-labs.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

static void randomString( char * dest, size_t length );
static void randomString( char * dest, size_t length )
{
    const char * c;
    size_t       i;
    
    c = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while( length-- )
    {
        i = ( size_t )( ( double )arc4random() / RAND_MAX * ( sizeof( c ) - 1 ) );
        
        *( dest++ ) = c[ i ];
    }
    
    *( dest ) = 0;
}

static void f( const void * k, const void * v );
static void f( const void * k, const void * v )
{
    fprintf( stderr, "%s: %s\n", ( const char * )k, ( const char * )v );
}

int main( void )
{
    {
        DictionaryRef       d;
        DictionaryCallbacks c;
        
        c = DictionaryStandardStringCallbacks();
        d = DictionaryCreate( 100, &c );
        
        DictionaryShow( d );
        
        DictionaryInsert( d, "foo", "hello, world" );
        DictionaryInsert( d, "bar", "hello, universe" );
        
        fprintf( stderr, "Has key 'foo':      %i\n", DictionaryKeyExists( d, "foo" ) );
        fprintf( stderr, "Has key 'bar':      %i\n", DictionaryKeyExists( d, "bar" ) );
        fprintf( stderr, "Has key 'foobar':   %i\n", DictionaryKeyExists( d, "foobar" ) );
        
        fprintf( stderr, "Value for 'foo':    %s\n", DictionaryGetValue( d, "foo" ) );
        fprintf( stderr, "Value for 'bar':    %s\n", DictionaryGetValue( d, "bar" ) );
        fprintf( stderr, "Value for 'foobar': %s\n", DictionaryGetValue( d, "foobar" ) );
        
        DictionaryShow( d );
        DictionaryInsert( d, "foo", "foobar" );
        DictionaryShow( d );
        DictionaryRemove( d, "bar" );
        
        fprintf( stderr, "Has key 'foo':      %i\n", DictionaryKeyExists( d, "foo" ) );
        fprintf( stderr, "Has key 'bar':      %i\n", DictionaryKeyExists( d, "bar" ) );
        fprintf( stderr, "Has key 'foobar':   %i\n", DictionaryKeyExists( d, "foobar" ) );
        
        DictionaryShow( d );
        DictionaryDelete( d );
    }
    
    fprintf( stderr, "--------------------------------------------------------------------------------\n" );
    
    {
        DictionaryRef       d;
        DictionaryCallbacks c;
        size_t              i;
        char                k[ 20 ];
        char                v[ sizeof( k ) ];
        
        c = DictionaryStandardStringCallbacks();
        d = DictionaryCreate( 1, &c );
        
        for( i = 1; i < sizeof( k ); i++ )
        {
            randomString( k, i );
            randomString( v, i );
            DictionaryInsert( d, k, v );
        }
        
        DictionaryShow( d );
        DictionaryDelete( d );
    }
    
    fprintf( stderr, "--------------------------------------------------------------------------------\n" );
    
    {
        DictionaryRef       d;
        DictionaryCallbacks c;
        size_t              i;
        char                k[ 20 ];
        char                v[ sizeof( k ) ];
        
        c = DictionaryStandardStringCallbacks();
        d = DictionaryCreate( 10, &c );
        
        for( i = 1; i < sizeof( k ); i++ )
        {
            randomString( k, i );
            randomString( v, i );
            DictionaryInsert( d, k, v );
        }
        
        DictionaryShow( d );
        DictionaryClear( d );
        DictionaryShow( d );
        DictionaryInsert( d, "foo", "bar" );
        DictionaryShow( d );
        DictionaryDelete( d );
    }
    
    fprintf( stderr, "--------------------------------------------------------------------------------\n" );
    
    {
        DictionaryRef       d;
        DictionaryCallbacks c;
        size_t              i;
        char                k[ 5 ];
        char                v[ sizeof( k ) ];
        
        c = DictionaryStandardStringCallbacks();
        d = DictionaryCreate( 10, &c );
        
        for( i = 1; i < sizeof( k ); i++ )
        {
            randomString( k, i );
            randomString( v, i );
            DictionaryInsert( d, k, v );
        }
        
        DictionaryApplyFunction( d, f );
        DictionaryShow( d );
        DictionaryDelete( d );
    }
    
    return 0;
}
