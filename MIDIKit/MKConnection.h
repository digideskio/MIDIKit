//
//  MKConnection.h
//  MIDIKit
//
//  Created by John Heaton on 4/11/14.
//  Copyright (c) 2014 John Heaton. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MKMessage.h"
#import "MKInputPort.h"
#import "MKOutputPort.h"
#import <JavaScriptCore/JavaScriptCore.h>

// A connection object is essentially a convenient way to
// send and receive from multiple sources and destinations
// without having to constantly iterate through a container
// and reference ports.
//
// Usage:
// MKConnection *connection = [MKConnection connectionWithClient:myClient];
// [connection addDestination:myDestination];
// [connection sendMessage:[MKMessage controlChangeMessageWithController:0 value:0]];

@protocol MKConnectionJS <JSExport>

+ (instancetype)new; // use global client
+ (instancetype)connectionWithClient:(MKClient *)client;

- (instancetype)sendMessageArray:(NSArray *)messages;
- (instancetype)sendMessage:(MKMessage *)message;

JSExportAs(send, - (instancetype)sendNumberArray:(NSArray *)array);

@property (nonatomic, weak) MKClient *client;
@property (nonatomic, strong) MKInputPort *inputPort;
@property (nonatomic, strong) MKOutputPort *outputPort;

- (instancetype)addDestination:(MKDestination *)destination;
- (instancetype)removeDestination:(MKDestination *)destination;
- (MKDestination *)destinationAtIndex:(NSUInteger)index;

@property (nonatomic, readonly) NSMutableArray *destinations;

@end


@interface MKConnection : NSObject <MKConnectionJS>

// NOTE: instantiation with a client will automatically
// create an input and output port from the client
// if they're not already created.
- (instancetype)initWithClient:(MKClient *)client;

// Async helper
- (instancetype)performBlock:(void (^)(MKConnection *c))block afterDelay:(NSTimeInterval)delay;

// Uses the output port to send to all destinations
- (instancetype)sendData:(NSData *)data;
- (instancetype)sendMessages:(MKMessage *)message, ... NS_REQUIRES_NIL_TERMINATION;

@end
