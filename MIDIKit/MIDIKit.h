//
//  MIDIKit.h
//  MIDIKit
//
//  Created by John Heaton on 4/13/14.
//  Copyright (c) 2014 John Heaton. All rights reserved.
//

#import <MIDIKit/MKClient.h>
#import <MIDIKit/MKConnection.h>
#import <MIDIKit/MKDevice.h>
#import <MIDIKit/MKEntity.h>
#import <MIDIKit/MKInputPort.h>
#import <MIDIKit/MKMessage.h>
#import <MIDIKit/MKObject.h>
#import <MIDIKit/MKOutputPort.h>
#import <MIDIKit/MKThruConnection.h>
#import <MIDIKit/MKVirtualDestination.h>
#import <MIDIKit/MKVirtualSource.h>
#import <MIDIKit/MKSource.h>
#import <MIDIKit/MKDestination.h>
#import <MIDIKit/MKServer.h>

#define kMIDIKitVersionMajor 0
#define kMIDIKitVersionMinor 2
#define kMIDIKitVersionPatch 1


// -------------------
// Global settings
// -------------------
//
// Whether or not to include all properties in -description of MKObject classes.
// This is handy to set to YES when inspecting objects
extern BOOL MKSettingDescriptionsIncludeProperties;     // default: NO

// Whether +evalOSStatus:name:throw: will throw an exception on error
extern BOOL MKSettingOSStatusEvaluationThrowsOnError;   // default: NO
// same for logging
extern BOOL MKSettingOSStatusEvaluationLogsOnError;     // default: YES if debug build, NO elsewise


// ------------------------------------------------------------------
// Convenience class methods for setting GLOBAL framework settings
// in the JavaScript world. You may use it as-is in Objective-C,
// however, note that it is only changing the global variables above
// directly, which you can do for the same effect.
//
// DO NOT INSTANTIATE THIS CLASS -- it will do no good
@protocol MIDIKitJS <JSExport>

JSExportAs(showProperties,  + (BOOL)setDescriptionsIncludeProperties:(BOOL)val);
JSExportAs(printErrors,     + (BOOL)setOSStatusEvaluationThrowsOnError:(BOOL)val);
JSExportAs(throwErrors,     + (BOOL)setOSStatusEvaluationLogsOnError:(BOOL)val);

+ (BOOL)descriptionsIncludeProperties;
+ (BOOL)OSStatusEvaluationLogsOnError;
+ (BOOL)OSStatusEvaluationThrowsOnError;

/**
 *  Opens the default web browser to the project page for MIDIKit.
 */
+ (void)openGitHub;

@end


@interface MIDIKit : NSObject <MIDIKitJS>

/**
 *  Checks an OSStatus, and prints/throws an error if configured to do so.
 *
 *  @param code The status code to evaluate.
 *  @param name The name of the operation which returned this code.
 *
 *  @return The status code.
 */
+ (OSStatus)evalOSStatus:(OSStatus)code name:(NSString *)name;

/**
 *  Loads all appropriate MIDIKit classes into a JavaScript context.
 *
 *  @param context The context in which to install the classes.
 */
+ (void)installIntoContext:(JSContext *)context;

@end