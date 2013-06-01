// ========================================================================= 
//  The contents of this file are subject to the Mozilla Public License      
//  Version 1.1 (the "License"); you may not use this file except in         
//  compliance with the License. You may obtain a copy of the License at     
//  http://www.mozilla.org/MPL/                                              
//                                                                           
//  Software distributed under the License is distributed on an "AS IS"      
//  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the  
//  License for the specific language governing rights and limitations       
//  under the License.                                                       
//                                                                           
//  The Original Code is the yavascript development system - web_globals.js. 
//                                                                           
//  The Initial Developer of the Original Code is Alex "Y_Less" Cole.        
// ========================================================================= 

// ==================================
//  
//  This file contains all objects
//  and properties defined in the
//  DOM specification(s) (or at
//  least a lot of them).
//  
//  Note that inclusion here does
//  not imply ability to make or
//  use these types directly, it
//  just means that they are defined
//  so where it is possible to use
//  them implicit global warnings
//  will not get thrown.
//  
//  Also note that although where
//  possible full object definitions
//  are included they are not used
//  in any way in the current tool
//  version.  They are merely here
//  for future possible expansions.
//  
//  Note: Trying to run this file
//  will probably screw your browser.
//  
// ==================================

// ====================================
//  
//  Conventions used in this document.
//  
//  Each entry is meant to represent
//  the item given, not implement it.
//  To this end, except for values
//  (i.e. constants), everything is
//  equal (though not equivalent) to
//  0, their exact value depending on
//  the type of the item.  For example
//  strings (or DOMStrings) are '',
//  booleans are false, numbers are 0
//  and objects are null.  Functions
//  are valid functions returning
//  their 0 value (or nothing).
//  DOMUserData is set to void 0,
//  this is as it can be any type and
//  is thus undefined.
//  
// ====================================

// =============
//  DOM Objects
// =============

// DOM String
// http://www.w3.org/TR/DOM-Level-3-Core/core.html#ID-C74D1578

var
	DOMString = String;

// DOM Time Stamp
// http://www.w3.org/TR/DOM-Level-3-Core/core.html#Core-DOMTimeStamp

var
	DOMTimeStamp = Date;

// DOM User Data
// http://www.w3.org/TR/DOM-Level-3-Core/core.html#Core-DOMUserData

var
	DOMUserData = void 0;

// DOM Object
// http://www.w3.org/TR/DOM-Level-3-Core/core.html#Core-DOMObject

var
	DOMObject = Object;

// Fundamental Interfaces
// http://www.w3.org/TR/DOM-Level-3-Core/core.html#ID-BBACDC08

var
	DOMException =
		{
			// Values
			// ExceptionCode
			INDEX_SIZE_ERR				: 1,
			DOMSTRING_SIZE_ERR			: 2,
			HIERARCHY_REQUEST_ERR		: 3,
			WRONG_DOCUMENT_ERR			: 4,
			INVALID_CHARACTER_ERR		: 5,
			NO_DATA_ALLOWED_ERR			: 6,
			NO_MODIFICATION_ALLOWED_ERR	: 7,
			NOT_FOUND_ERR				: 8,
			NOT_SUPPORTED_ERR			: 9,
			INUSE_ATTRIBUTE_ERR			: 10,
			INVALID_STATE_ERR			: 11,
			SYNTAX_ERR					: 12,
			INVALID_MODIFICATION_ERR	: 13,
			NAMESPACE_ERR				: 14,
			INVALID_ACCESS_ERR			: 15,
			VALIDATION_ERR				: 16,
			TYPE_MISMATCH_ERR			: 17,
			// Attributes
			code	: 0
		},
	// This object is listed
	// separately in some places
	// and in DOMException in
	// others.  It is included
	// here for completeness.
	ExceptionCode =
		{
			// Values
			// ExceptionCode
			INDEX_SIZE_ERR				: 1,
			DOMSTRING_SIZE_ERR			: 2,
			HIERARCHY_REQUEST_ERR		: 3,
			WRONG_DOCUMENT_ERR			: 4,
			INVALID_CHARACTER_ERR		: 5,
			NO_DATA_ALLOWED_ERR			: 6,
			NO_MODIFICATION_ALLOWED_ERR	: 7,
			NOT_FOUND_ERR				: 8,
			NOT_SUPPORTED_ERR			: 9,
			INUSE_ATTRIBUTE_ERR			: 10,
			INVALID_STATE_ERR			: 11,
			SYNTAX_ERR					: 12,
			INVALID_MODIFICATION_ERR	: 13,
			NAMESPACE_ERR				: 14,
			INVALID_ACCESS_ERR			: 15,
			VALIDATION_ERR				: 16,
			TYPE_MISMATCH_ERR			: 17
		},
	DOMStringList =
		{
			// Attributes
			length	: 0,
			// Methods
			item		:
				function (index)
				{
					return null;
				},
			contains	:
				function (str)
				{
					return false;
				}
		},
	DOMImplementationList =
		{
			// Attributes
			length	: 0,
			// Methods
			item	:
				function (index)
				{
					return null;
				}
		},
	DOMImplementationSource = 
		{
			// Methods
			getDOMImplementation		:
				function (features)
				{
					return null;
				},
			getDOMImplementationList	:
				function (features)
				{
					return null;
				}
		},
	DOMImplementation =
		{
			// Methods
			hasFeature			:
				function (feature, version) 
				{
					return false;
				},
			createDocumentType	:
				function (qualifiedName, publicId, systemId)
				{
					return null;
				},
			createDocument		:
				function (namespaceURI, qualifiedName, doctype)
				{
					return null;
				},
			getFeature			:
				function (feature, version)
				{
					return {};
				}
		},
	DOMImplementationRegistry =
		{
			// Methods
			getDOMImplementation		:
				function (features)
				{
					return null;
				},
			getDOMImplementationList	:
				function (features)
				{
					return null;
				}
		},
	DocumentFragment =
		{
		},
	Document =
		{
			// Attributes
			doctype				: null,
			implementation		: null,
			documentElement		: null,
			imputEncoding		: '',
			xmlEncoding			: '',
			xmlStandalone		: false,
			xmlVersion			: '',
			strictErrorChecking	: false,
			documentURI			: '',
			domConfig			: '',
			// Methods
			createElement				:
				function (tagName)
				{
					return null;
				},
			createDocumentFragment		:
				function ()
				{
					return null;
				},
			createTextNode				:
				function (data)
				{
					return null;
				},
			createComment				:
				function (data)
				{
					return null;
				},
			createCDATASection			:
				function (data)
				{
					return null;
				},
			createProcessingInstruction	:
				function (target, data)
				{
					return null;
				},
			createAttribute				:
				function (name)
				{
					return null;
				},
			createEntityReference		:
				function (name)
				{
					return null;
				},
			getElementsByTagName		:
				function (tagname)
				{
					return null;
				},
			importNode					:
				function (importedNode, deep)
				{
					return null;
				},
			createElementNS				:
				function (namespaceURI, qualifiedName)
				{
					return null;
				},
			createAttributeNS			:
				function (namespaceURI, qualifiedName)
				{
					return null;
				},
			getElementsByTagNameNS		:
				function (namespaceURI, localName)
				{
					return null;
				},
			getElementById				:
				function (elementId)
				{
					return null;
				},
			adoptNode					:
				function (source)
				{
					return null;
				},
			normalizeDocument			:
				function ()
				{
					return;
				},
			renameNode					:
				function (n, namespaceURI, qualifiedName)
				{
					return null;
				}
		},
	Node =
		{
			// Values
			// NodeType
			ELEMENT_NODE				: 1,
			ATTRIBUTE_NODE				: 2,
			TEXT_NODE					: 3,
			CDATA_SECTION_NODE			: 4,
			ENTITY_REFERENCE_NODE		: 5,
			ENTITY_NODE					: 6,
			PROCESSING_INSTRUCTION_NODE	: 7,
			COMMENT_NODE				: 8,
			DOCUMENT_NODE				: 9,
			DOCUMENT_TYPE_NODE			: 10,
			DOCUMENT_FRAGMENT_NODE		: 11,
			NOTATION_NODE				: 12,
			// DocumentPosition
			DOCUMENT_POSITION_DISCONNECTED				: 0x01,
			DOCUMENT_POSITION_PRECEDING					: 0x02,
			DOCUMENT_POSITION_FOLLOWING					: 0x04,
			DOCUMENT_POSITION_CONTAINS					: 0x08,
			DOCUMENT_POSITION_CONTAINED_BY				: 0x10,
			DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC	: 0x20,
			// Attributes
			nodeName		: '',
			nodeValue		: '',
			nodeType		: 0,
			parentNode		: null,
			childNodes		: null,
			firstChild		: null,
			lastChild		: null,
			previousSibling	: null,
			nextSibling		: null,
			attributes		: null,
			ownerDocument	: null,
			namespaceURI	: '',
			prefix			: '',
			localName		: '',
			baseURI			: null,
			textContent		: '',
			// Methods
			insertBefore		:
				function (newChild, refChild)
				{
					return null;
				},
			replaceChild		:
				function (newChild, oldChild)
				{
					return null;
				},
			removeChild			:
				function (oldChild)
				{
					return null;
				},
			appendChild			:
				function (newChild)
				{
					return null;
				},
			hasChildNodes		:
				function ()
				{
					return false;
				},
			cloneNode			:
				function (deep)
				{
					return null;
				},
			normalize			:
				function ()
				{
					return;
				},
			isSupported			:
				function (feature, version)
				{
					return false;
				},
			hasAttributes		:
				function ()
				{
					return false;
				},
			isSameNode			:
				function (other)
				{
					return false;
				},
			lookupPrefix		:
				function (namespaceURI)
				{
					return '';
				},
			isDefaultNamespace	:
				function (namespaceURI)
				{
					return false;
				},
			lookupNamespaceURI	:
				function (prefix)
				{
					return '';
				},
			isEqualNode			:
				function (arg)
				{
					return false;
				},
			getFeature			:
				function (feature, version)
				{
					return {};
				},
			setUserData			:
				function (key, data, handler)
				{
					return void 0;
				},
			getUserData			:
				function (key)
				{
					return void 0;
				}
		},
	NodeList =
		{
			// Attributes
			length	: 0,
			// Methods
			item	:
				function (index)
				{
					return null;
				}
		},
	NamedNodeMap =
		{
			// Attributes
			length	: 0,
			// Methods
			getNamedItem		:
				function (name)
				{
					return null;
				},
			setNamedItem		:
				function (arg)
				{
					return null;
				},
			removeNamedItem		:
				function (name)
				{
					return null;
				},
			item				:
				function (index)
				{
					return null;
				},
			getNamedItemNS		:
				function (namespaceURI, localName)
				{
					return null;
				},
			setNamedItemNS		:
				function (arg)
				{
					return null;
				},
			removeNamedItemNS	:
				function (namespaceURI, localName)
				{
					return null;
				}
		},
	CharacterData =
		{
			// Attributes
			data	: '',
			length	: 0,
			// Methods
			substringData	:
				function (offset, count)
				{
					return '';
				},
			appendData		:
				function (arg)
				{
					return;
				},
			insertData		:
				function (offset, arg)
				{
					return;
				},
			deleteData		:
				function (offset, count)
				{
					return;
				},
			replaceData		:
				function (offset, count, arg)
				{
					return;
				}
		},
	Attr =
		{
			// Attributes
			name			: '',
			specified		: false,
			value			: '',
			ownerElement	: null,
			schemaTypeInfo	: null,
			isId			: false
		},
	Element =
		{
			// Attributes
			tagName			: '',
			schemaTypeInfo	: null,
			// Methods
			getAttribute			:
				function (name)
				{
					return '';
				},
			setAttribute			:
				function (name, value)
				{
					return;
				},
			removeAttribute			:
				function (name)
				{
					return;
				},
			getAttributeNode		:
				function (name)
				{
					return null;
				},
			setAttributeNode		:
				function (newAttr)
				{
					return null;
				},
			removeAttributeNode		:
				function (oldAttr)
				{
					return null;
				},
			getElementsByTagName	:
				function (name)
				{
					return null;
				},
			getAttributeNS			:
				function (namespaceURI, localName)
				{
					return '';
				},
			setAttributeNS			:
				function (namespaceURI, qualifiedName, value)
				{
					return;
				},
			removeAttributeNS		:
				function (namespaceURI, localName)
				{
					return;
				},
			getAttributeNodeNS		:
				function (namespaceURI, localName)
				{
					return null;
				},
			setAttributeNodeNS		:
				function (newAttr)
				{
					return null;
				},
			getElementsByTagNameNS	:
				function (namespaceURI, localName)
				{
					return null;
				},
			hasAttribute			:
				function (name)
				{
					return false;
				},
			hasAttributeNS			:
				function (namespaceURI, localName)
				{
					return false;
				},
			setIdAttribute			:
				function (name, isId)
				{
					return;
				},
			setIdAttributeNS		:
				function (namespaceURI, localName, isId)
				{
					return;
				},
			setIDAttributeNode		:
				function (idAttr, isId)
				{
					return;
				}
		},
	Text =
		{
			// Attributes
			isElementContentWhitespace	: false,
			wholeText					: '',
			// Methods
			splitText			:
				function (offset)
				{
					return null;
				},
			replaceWholeText	:
				function (content)
				{
					return null;
				}
		},
	Comment =
		{
		},
	TypeInfo =
		{
			// Values
			// DerivationMethods
			DERIVATION_RESTRICTION	: 0x01,
			DERIVATION_EXTENSION	: 0x02,
			DERIVATION_UNION		: 0x04,
			DERIVATION_LIST			: 0x08,
			// Attributes
			typeName		: '',
			typeNamespace	: '',
			// Methods
			isDerivedFrom	:
				function (typeNamespaceArg, typeNameArg, derivationMethod)
				{
					return false;
				}
		},
	UserDataHandler =
		{
			// Values
			// OperationType
			NODE_CLONED		: 1,
			NODE_IMPORTED	: 2,
			NODE_DELETED	: 3,
			NODE_RENAMED	: 4,
			NODE_ADOPTED	: 5,
			// Methods
			handle	:
				function (operation, key, data, src, dst)
				{
					return;
				}
		},
	DOMError =
		{
			// Values
			// ErrorSeverity
			SEVERITY_WARNING		: 1,
			SEVERITY_ERROR			: 2,
			SEVERITY_FATAL_ERROR	: 3,
			// Attributes
			severity			: 0,
			message				: '',
			type				: '',
			relatedException	: {},
			relatedData			: {},
			location			: null
		},
	DOMErrorHandler =
		{
			// Methods
			handleError	:
				function (error)
				{
					return false;
				}
		},
	DOMLocator =
		{
			// Attributes
			lineNumber		: 0,
			columnNumber	: 0,
			byteOffset		: 0,
			utf16Offset		: 0,
			relatedNode		: null,
			uri				: ''
		},
	DOMConfiguration =
		{
			// Attributes
			parameterNames	: null,
			// Methods
			setParameter	:
				function (name, value)
				{
					return;
				},
			getParameter	:
				function (name)
				{
					return void 0;
				},
			canSetParameter	:
				function (name, value)
				{
					return false;
				}
		};

// Extended Interfaces
// http://www.w3.org/TR/DOM-Level-3-Core/core.html#ID-E067D597

var
	CDATASection =
		{
		},
	DocumentType =
		{
			// Attributes
			name			: '',
			entities		: null,
			notations		: null,
			publicId		: '',
			systemId		: '',
			internalSubset	: ''
		},
	Notation =
		{
			// Attributes
			publicId	: '',
			systemId	: ''
		},
	Entity =
		{
			// Attributes
			publicId		: '',
			systemId		: '',
			notationName	: '',
			inputEncoding	: '',
			xmlEncoding		: '',
			xmlVersion		: ''
		},
	EntityReference =
		{
		},
	ProcessingInstruction =
		{
			target	: '',
			data	: ''
		};

// View Interfaces
// http://www.w3.org/TR/2000/REC-DOM-Level-2-Views-20001113/views.html#Views-Interfaces

var
	AbstractView =
		{
			// Attributes
			document	: null
		},
	DocumentView =
		{
			defaultView	: null
		};

// Formal Interface Definition
// http://www.w3.org/TR/2000/REC-DOM-Level-2-Traversal-Range-20001113/traversal.html#Traversal-IDLDefinition

var
	NodeIterator =
		{
			// Attributes
			root					: null,
			whatToShow				: 0,
			filter					: null,
			expandEntityReferences	: false,
			// Methods
			nextNode		:
				function ()
				{
					return null;
				},
			previousNode	:
				function ()
				{
					return null;
				},
			detach			:
				function ()
				{
					return;
				}
		},
	NodeFilter =
		{
			// Values
			// Constants Returned By acceptNode
			FILTER_ACCEPT	: 1,
			FILTER_REJECT	: 2,
			FILTER_SKIP		: 3,
			// Constants For whatToShow
			SHOW_ALL					: 0xFFFFFFFF,
			SHOW_ELEMENT				: 0x00000001,
			SHOW_ATTRIBUTE				: 0x00000002,
			SHOW_TEXT					: 0x00000004,
			SHOW_CDATA_SECTION			: 0x00000008,
			SHOW_ENTITY_REFERENCE		: 0x00000010,
			SHOW_ENTITY					: 0x00000020,
			SHOW_PROCESSING_INSTRUCTION	: 0x00000040,
			SHOW_COMMENT				: 0x00000080,
			SHOW_DOCUMENT				: 0x00000100,
			SHOW_DOCUMENT_TYPE			: 0x00000200,
			SHOW_DOCUMENT_FRAGMENT		: 0x00000400,
			SHOW_NOTATION				: 0x00000800,
			// Methods
			acceptNode	:
				function ()
				{
					return 0;
				}
		},
	TreeWalker =
		{
			// Attributes
			root					: null,
			whatToShow				: 0,
			filter					: null,
			expandEntityReferences	: false,
			currentNode				: null,
			// Methods
			parentNode		:
				function ()
				{
					return null;
				},
			firstChild		:
				function ()
				{
					return null;
				},
			lastChild		:
				function ()
				{
					return null;
				},
			previousSibling	:
				function ()
				{
					return null;
				},
			nextSibling		:
				function ()
				{
					return null;
				},
			previousNode	:
				function ()
				{
					return null;
				},
			nextNode		:
				function ()
				{
					return null;
				}
		},
	DocumentTraversal =
		{
			// Methods
			createNodeIterator	:
				function (root, whatToShow, filter, entityReferenceExpansion)
				{
					return null;
				},
			createTreeWalker	:
				function (root, whatToShow, filter, entityReferenceExpansion)
				{
					return null;
				}
		};

// Formal Description Of The Range Interface
// http://www.w3.org/TR/2000/REC-DOM-Level-2-Traversal-Range-20001113/ranges.html#Level-2-Range-Interface

var
	Range =
		{
			// Values
			// CompareHow
			START_TO_START	: 0,
			START_TO_END	: 1,
			END_TO_END		: 2,
			END_TO_START	: 3,
			// Attributes
			startContainer			: null,
			startOffset				: 0,
			endContainer			: null,
			endOffset				: 0,
			collapsed				: false,
			commonAncestorContainer	: null,
			// Methods
			setStart				:
				function (refNode, offset)
				{
					return;
				},
			setEnd					:
				function (refNode, offset)
				{
					return;
				},
			setStartBefore			:
				function (refNode)
				{
					return;
				},
			setStartAfter			:
				function (refNode)
				{
					return;
				},
			setEndBefore			:
				function (refNode)
				{
					return;
				},
			setEndAfter				:
				function (refNode)
				{
					return;
				},
			collapse				:
				function (toStart)
				{
					return;
				},
			selectNode				:
				function (refNode)
				{
					return;
				},
			selectNodeContents		:
				function (refNode)
				{
					return;
				},
			compareBoundaryPoints	:
				function (how, sourceRange)
				{
					return 0;
				},
			deleteContents			:
				function ()
				{
					return;
				},
			extractContents			:
				function ()
				{
					return null;
				},
			cloneContents			:
				function ()
				{
					return null;
				},
			insertNode				:
				function (newNode)
				{
					return;
				},
			surroundContents		:
				function (newParent)
				{
					return;
				},
			cloneRange				:
				function ()
				{
					return null;
				},
			toString				:
				function ()
				{
					return '';
				},
			detach					:
				function ()
				{
					return;
				}
		},
	DocumentRange =
		{
			// Methods
			createRange	:
				function ()
				{
					return null;
				}
		},
	RangeException =
		{
			// Values
			// RangeExceptionCode
			BAD_BOUNDARYPOINTS_ERR	: 1,
			INVALID_NODE_TYPE_ERR	: 2,
			// Attributes
			code	: 0
		},
	// This object is listed
	// separately in some places
	// and in RangeException in
	// others.  It is included
	// here for completeness.
	RangeExceptionCode =
		{
			// Values
			// RangeExceptionCode
			BAD_BOUNDARYPOINTS_ERR	: 1,
			INVALID_NODE_TYPE_ERR	: 2
		};

// Exceptions
// http://www.w3.org/TR/2004/REC-DOM-Level-3-Val-20040127/validation.html#Exception

var
	ExceptionVAL =
		{
			// Values
			// ExceptionVALCode
			NO_SCHEMA_AVAILABLE_ERR	: 71,
			// Attributes
			code	: 0
		},
	// This object is listed
	// separately in some places
	// and in ExceptionVAL in
	// others.  It is included
	// here for completeness.
	ExceptionVALCode =
		{
			// Values
			// ExceptionVALCode
			NO_SCHEMA_AVAILABLE_ERR	: 71
		};
// Document Editing Interfaces
// http://www.w3.org/TR/2004/REC-DOM-Level-3-Val-20040127/validation.html#DocumentEditing

var
	DocumentEditVAL =
		{
			// Attributes
			continuousValidityChecking	: false,
			domConfig					: null,
			// Methods
			getDefinedElements	:
				function (namespaceURI)
				{
					return null;
				},
			validateDocument	:
				function ()
				{
					return 0;
				}
		},
	NodeEditVAL =
		{
			// Values
			// validationType
			VAL_WF			: 1,
			VAL_NS_WF		: 2,
			VAL_INCOMPLETE	: 3,
			VAL_SCHEMA		: 4,
			// validationState
			VAL_TRUE	: 5,
			VAL_FALSE	: 6,
			VAL_UNKNOWN	: 7,
			// Attributes
			defaultValue		: '',
			enumeratedValues	: '',
			// Methods
			canInsertBefore	:
				function (newChild, refChild)
				{
					return 0;
				},
			canRemoveChild	:
				function (oldChild)
				{
					return 0;
				},
			canReplaceChild	:
				function (newChild, oldChild)
				{
					return 0;
				},
			canAppendChild	:
				function (newChild)
				{
					return 0;
				},
			nodeValidity	:
				function (valType)
				{
					return 0;
				}
		},
	ElementEditVAL =
		{
			// Values
			// ContentTypeVAL
			VAL_EMPTY_CONTENTTYPE		: 1,
			VAL_ANY_CONTENTTYPE			: 2,
			VAL_MIXED_CONTENTTYPE		: 3,
			VAL_ELEMENTS_CONTENTTYPE	: 4,
			VAL_SIMPLE_CONTENTTYPE		: 5,
			// Attributes
			allowedChildren			: null,
			allowedFirstChildren	: null,
			allowedParents			: null,
			allowedNextSiblings		: null,
			allowedPreviousSiblings	: null,
			allowedAttributes		: null,
			requiredAttributes		: null,
			contentType				: 0,
			// Methods
			canSetTextContent		:
				function (possibleTextContent)
				{
					return 0;
				},
			canSetAttribute			:
				function (attrname, attrval)
				{
					return 0;
				},
			canSetAttributeNode		:
				function (attrNode)
				{
					return 0;
				},
			canSetAttributeNS		:
				function (namespaceURI, qualifiedName, value)
				{
					return 0;
				},
			canRemoveAttribute		:
				function (attrname)
				{
					return 0;
				},
			canRemoveAttributeNS	:
				function (namespaceURI, localName)
				{
					return 0;
				},
			canRemoveAttributeNode	:
				function (attrNode)
				{
					return 0;
				},
			isElementDefined		:
				function (name)
				{
					return 0;
				},
			isElementDefinedNS		:
				function (namespaceURI, name)
				{
					return 0;
				}
		},
	CharacterDataEditVAL =
		{
			// Methods
			isWhitespaceOnly	:
				function ()
				{
					return 0;
				},
			canSetData			:
				function (arg)
				{
					return 0;
				},
			canAppendData		:
				function (arg)
				{
					return 0;
				},
			canReplaceData		:
				function (offset, count, arg)
				{
					return 0;
				},
			canInsertData		:
				function (offset, arg)
				{
					return 0;
				},
			canDeleteData		:
				function (offset, count)
				{
					return 0;
				}
		};

// The LSInputStream Type
// http://www.w3.org/TR/2004/REC-DOM-Level-3-LS-20040407/load-save.html#LS-LSInputStream

var
	LSInputStream = Object;

// The LSOutputStream Type
// http://www.w3.org/TR/2004/REC-DOM-Level-3-LS-20040407/load-save.html#LS-LSOutputStream

var
	LSOutputStream = Object;

// The LSReader Type
// http://www.w3.org/TR/2004/REC-DOM-Level-3-LS-20040407/load-save.html#LS-LSReader

var
	LSReader = null;

// The LSWriter Type
// http://www.w3.org/TR/2004/REC-DOM-Level-3-LS-20040407/load-save.html#LS-LSWriter

var
	LSWriter = null;

// Fundamental Interfaces
// http://www.w3.org/TR/2004/REC-DOM-Level-3-LS-20040407/load-save.html#LS-fundamental

var
	LSException =
		{
			// Values
			// LSExceptionCode
			PARSE_ERR		: 81,
			SERIALIZE_ERR	: 82,
			// Attributes
			code	: 0
		},
	// This object is listed
	// separately in some places
	// and in LSException in
	// others.  It is included
	// here for completeness.
	LSExceptionCode =
		{
			// Values
			// LSExceptionCode
			PARSE_ERR		: 81,
			SERIALIZE_ERR	: 82
		},
	DOMImplementationLS =
		{
			// Values
			// DOMImplementationLSMode
			MODE_SYNCHRONOUS	: 1,
			MODE_ASYNCHRONOUS	: 2,
			// Methods
			createLSParser		:
				function (mode, schemaType)
				{
					return null;
				},
			createLSSerializer	:
				function ()
				{
					return null;
				},
			createLSInput		:
				function ()
				{
					return null;
				},
			createLSOutput		:
				function ()
				{
					return null;
				}
		},
	LSParser =
		{
			// Values
			// ACTION_TYPES
			ACTION_APPEND_AS_CHILDREN	: 1,
			ACTION_REPLACE_CHILDREN		: 2,
			ACTION_INSERT_BEFORE		: 3,
			ACTION_INSERT_AFTER			: 4,
			ACTION_REPLACE				: 5,
			// Attributes
			domConfig	: null,
			filter		: null,
			async		: false,
			busy		: false,
			// Methods
			parse				:
				function (input)
				{
					return null;
				},
			parseURI			:
				function (uri)
				{
					return null;
				},
			parseWithContext	:
				function (input, contextArg, action)
				{
					return null;
				},
			abort				:
				function ()
				{
					return;
				}
		},
	LSInput =
		{
			// Attributes
			characterStream	: null,
			byteStream		: null,
			stringDate		: '',
			systemId		: '',
			publicId		: '',
			baseURI			: '',
			encoding		: '',
			certifiedText	: false
		},
	LSResourceResolver =
		{
			// Methods
			resolveResource	:
				function (type, namespaceURI, publicId, systemId, baseURI)
				{
					return null;
				}
		},
	LSParserFilter =
		{
			// Values
			// Constants Returned By startElement And acceptNode
			FILTER_ACCEPT		: 1,
			FILTER_REJECT		: 2,
			FILTER_SKIP			: 3,
			FILTER_INTERRUPT	: 4,
			// Attributes
			whatToShow	: 0,
			// Methods
			startElement	:
				function (elementArg)
				{
					return 0;
				},
			acceptNode		:
				function (nodeArg)
				{
					return 0;
				}
		},
	LSProgressEvent =
		{
			// Attributes
			input		: null,
			position	: 0,
			totalSize	: 0
		},
	LSLoadEvent =
		{
			// Attributes
			newDocument	: null,
			input		: null
		},
	LSSerializer =
		{
			// Attributes
			domConfig	: null,
			newLine		: '',
			// Methods
			write			:
				function (nodeArg, destination)
				{
					return false;
				},
			writeToURI		:
				function (nodeArg, uri)
				{
					return false;
				},
			writeToString	:
				function (nodeArg)
				{
					return '';
				}
		},
	LSOutput =
		{
			// Attributes
			characterStream	: null,
			byteStream		: null,
			systemId		: '',
			encoding		: ''
		},
	LSSerializerFilter =
		{
			// Attributes
			whatToShow	:	0
		};

// Style Sheet Interfaces
// http://www.w3.org/TR/2000/REC-DOM-Level-2-Style-20001113/stylesheets.html#StyleSheets-fundamental

var
	StyleSheet =
		{
			// Attributes
			type				: '',
			disabled			: false,
			ownerNode			: null,
			parentStyleSheet	: null,
			href				: '',
			title				: '',
			media				: null
		},
	StyleSheetList =
		{
			// Attributes
			length	: 0,
			// Methods
			item	:
				function (index)
				{
					return null;
				}
		},
	MediaList =
		{
			// Attributes
			mediaText	: '',
			length		: 0,
			// Methods
			item			:
				function (index)
				{
					return '';
				},
			deleteMedium	:
				function (oldMedium)
				{
					return;
				},
			appendMedium	:
				function (newMedium)
				{
					return;
				}
		};

// Document Extensions
// http://www.w3.org/TR/2000/REC-DOM-Level-2-Style-20001113/stylesheets.html#StyleSheets-extensions

var
	LinkStyle =
		{
			// Attributes
			sheet	: null
		},
	DocumentStyle =
		{
			// Attributes
			styleSheets	: null
		};

// CSS Fundamental Interfaces
// http://www.w3.org/TR/2000/REC-DOM-Level-2-Style-20001113/css.html#CSS-fundamental

var
	CSSStyleSheet =
		{
			// Attributes
			ownerRule	: null,
			cssRules	: null,
			// Methods
			insertRule	:
				function (rule, index)
				{
					return 0;
				},
			deleteRule	:
				function (index)
				{
					return;
				}
		},
	CSSRuleList =
		{
			// Attributes
			index	: 0,
			// Methods
			item	:
				function (index)
				{
					return null;
				}
		},
	CSSRule =
		{
			// Values
			// RuleType
			UNKNOWN_RULE	: 0,
			STYLE_RULE		: 1,
			CHARSET_RULE	: 2,
			IMPORT_RULE		: 3,
			MEDIA_RULE		: 4,
			FONT_FACE_RULE	: 5,
			PAGE_RULE		: 6,
			// Attributes
			type				: 0,
			cssText				: '',
			parentStyleSheet	: null,
			parentRule			: null
		},
	CSSStyleRule =
		{
			// Attributes
			selectorText	: '',
			style			: null
		},
	CSSMediaRule =
		{
			// Attributes
			media		: null,
			cssRules	: null,
			// Methods
			insertRule	:
				function (rule, index)
				{
					return 0;
				},
			deleteRule	:
				function (index)
				{
					return;
				}
		},
	CSSFontFaceRule =
		{
			// Attributes
			style	: null
		},
	CSSPageRule =
		{
			// Attributes
			selectorText	: '',
			style			: null
		},
	CSSImportRule =
		{
			// Attributes
			href		: '',
			media		: null,
			styleSheet	: null
		},
	CSSCharsetRule =
		{
			// Attributes
			encoding	: ''
		},
	CSSUnknownRule =
		{
		},
	CSSStyleDeclaration =
		{
			// Attributes
			cssText		: '',
			length		: 0,
			parentRule	: null,
			// Methods
			getPropertyValue	:
				function (propertyName)
				{
					return '';
				},
			getPropertyCSSValue	:
				function (propertyName)
				{
					return null;
				},
			removeProperty		:
				function (propertyName)
				{
					return '';
				},
			getPropertyPriority	:
				function (propertyName)
				{
					return '';
				},
			setProperty			:
				function (propertyName, value, priority)
				{
					return;
				},
			item				:
				function (index)
				{
					return '';
				}

		},
	CSSValue =
		{
			// Values
			// UnitTypes
			CSS_INHERIT			: 0,
			CSS_PRIMITIVE_VALUE	: 1,
			CSS_VALUE_LIST		: 2,
			CSS_CUSTOM			: 3,
			// Attributes
			cssText			: '',
			cssValueType	: 0
		},
	CSSPrimitiveValue =
		{
			// Values
			// UnitType
			CSS_UNKNOWN		: 0,
			CSS_NUMBER		: 1,
			CSS_PERCENTAGE	: 2,
			CSS_EMS			: 3,
			CSS_EXS			: 4,
			CSS_PX			: 5,
			CSS_CM			: 6,
			CSS_MM			: 7,
			CSS_IN			: 8,
			CSS_PT			: 9,
			CSS_PC			: 10,
			CSS_DEG			: 11,
			CSS_RAD			: 12,
			CSS_GRAD		: 13,
			CSS_MS			: 14,
			CSS_S			: 15,
			CSS_HZ			: 16,
			CSS_KHZ			: 17,
			CSS_DIMENSION	: 18,
			CSS_STRING		: 19,
			CSS_URI			: 20,
			CSS_IDENT		: 21,
			CSS_ATTR		: 22,
			CSS_COUNTER		: 23,
			CSS_RECT		: 24,
			CSS_RGBCOLOR	: 25,
			// Attributes
			primitiveType	: 0,
			// Methods
			setFloatValue		:
				function (unitType, floatValue)
				{
					return;
				},
			getFloatValue		:
				function (unitType)
				{
					return 0.0;
				},
			setStringValue		:
				function (stringType, stringValue)
				{
					return;
				},
			getStringValue		:
				function ()
				{
					return '';
				},
			getCounterValue		:
				function ()
				{
					return null;
				},
			getRectValue		:
				function ()
				{
					return null;
				},
			getRGBColorValue	:
				function ()
				{
					return null;
				}
		},
	CSSValueList =
		{
			// Attributes
			length	: 0,
			// Methods
			item	:
				function (index)
				{
					return null;
				}
		},
	RGBColor =
		{
			// Attributes
			red		: null,
			green	: null,
			blue	: null
		},
	Rect =
		{
			// Attributes
			top		: null,
			right	: null,
			bottom	: null,
			left	: null
		},
	Counter =
		{
			// Attributes
			identifier	: '',
			listStyle	: '',
			separator	: ''
		};

// Override and computed style sheet
// http://www.w3.org/TR/2000/REC-DOM-Level-2-Style-20001113/css.html#CSS-OverrideAndComputed

var
	ViewCSS =
		{
			// Methods
			getComputedStyle	:
				function (elt, pseudoElt)
				{
					return null;
				}
		},
	DocumentCSS =
		{
			// Methods
			getOverrideStyle	:
				function (elt, pseudoElt)
				{
					return null;
				}
		};

// Style Sheet Creation
// http://www.w3.org/TR/2000/REC-DOM-Level-2-Style-20001113/css.html#CSS-StyleSheetCreation

var
	DOMImplementationCSS =
		{
			// Methods
			createCSSStyleSheet	:
				function (title, media)
				{
					return null;
				}
		};

// Element With CSS Inline Style
// http://www.w3.org/TR/2000/REC-DOM-Level-2-Style-20001113/css.html#CSS-htmlelementcss

var
	ElementCSSInlineStyle =
		{
			// Attributes
			style	: null
		};

// CSS2 Extended Interface
// http://www.w3.org/TR/2000/REC-DOM-Level-2-Style-20001113/css.html#CSS-extended

var
	CSS2Properties =
		{
			// Attributes
			azimuth					: '',
			background				: '',
			backgroundAttachment	: '',
			backgroundColor			: '',
			backgroundImage			: '',
			backgroundPosition		: '',
			backgroundRepeat		: '',
			border					: '',
			borderCollapse			: '',
			borderColor				: '',
			borderSpacing			: '',
			borderStyle				: '',
			borderTop				: '',
			borderRight				: '',
			borderBottom			: '',
			borderLeft				: '',
			borderTopColor			: '',
			borderRightColor		: '',
			borderBottomColor		: '',
			borderLeftColor			: '',
			borderTopStyle			: '',
			borderRightStyle		: '',
			borderBottomStyle		: '',
			borderLeftStyle			: '',
			borderTopWidth			: '',
			borderRightWidth		: '',
			borderBottomWidth		: '',
			borderLeftWidth			: '',
			borderWidth				: '',
			bottom					: '',
			captionSide				: '',
			clear					: '',
			clip					: '',
			color					: '',
			content					: '',
			counterIncrement		: '',
			counterReset			: '',
			cue						: '',
			cueAfter				: '',
			cueBefore				: '',
			cursor					: '',
			direction				: '',
			display					: '',
			elevation				: '',
			emptyCells				: '',
			cssFloat				: '',
			font					: '',
			fontFamily				: '',
			fontSize				: '',
			fontSizeAdjust			: '',
			fontStretch				: '',
			fontStyle				: '',
			fontVariant				: '',
			fontWeight				: '',
			height					: '',
			left					: '',
			letterSpacing			: '',
			lineHeight				: '',
			listStyle				: '',
			listStyleImage			: '',
			listStylePosition		: '',
			listStyleType			: '',
			margin					: '',
			marginTop				: '',
			marginRight				: '',
			marginBottom			: '',
			marginLeft				: '',
			markerOffset			: '',
			marks					: '',
			maxHeight				: '',
			maxWidth				: '',
			minHeight				: '',
			minWidth				: '',
			orphans					: '',
			outline					: '',
			outlineColor			: '',
			outlineStyle			: '',
			outlineWidth			: '',
			overflow				: '',
			padding					: '',
			paddingTop				: '',
			paddingRight			: '',
			paddingBottom			: '',
			paddingLeft				: '',
			page					: '',
			pageBreakAfter			: '',
			pageBreakBefore			: '',
			pageBreakInside			: '',
			pause					: '',
			pauseAfter				: '',
			pauseBefore				: '',
			pitch					: '',
			pitchRange				: '',
			playDuring				: '',
			position				: '',
			quotes					: '',
			richness				: '',
			right					: '',
			size					: '',
			speak					: '',
			speakHeader				: '',
			speakNumeral			: '',
			speakPunctuation		: '',
			speechRate				: '',
			stress					: '',
			tableLayout				: '',
			textAlign				: '',
			textDecoration			: '',
			textIndent				: '',
			textShadow				: '',
			textTransform			: '',
			top						: '',
			unicodeBidi				: '',
			verticalAlign			: '',
			visibility				: '',
			voiceFamily				: '',
			volume					: '',
			whiteSpace				: '',
			widows					: '',
			width					: '',
			wordSpacing				: '',
			zIndex					: ''
		};

// Miscellaneous Object Definitions
// http://www.w3.org/TR/DOM-Level-2-HTML/html.html#ID-1019015399

var
	HTMLCollection =
		{
			// Attributes
			length	: 0,
			// Methods
			item		:
				function  (index)
				{
					return null;
				},
			namedItem	:
				function (name)
				{
					return null;
				}
		},
	HTMLOptionsCollection =
		{
			// Attributes
			length	: 0,
			// Methods
			item		:
				function  (index)
				{
					return null;
				},
			namedItem	:
				function (name)
				{
					return null;
				}
		};

// Objects Related To HTML Documents
// http://www.w3.org/TR/DOM-Level-2-HTML/html.html#ID-1006298752

var
	HTMLDocument =
		{
			// Attributes
			title		: '',
			referrer	: '',
			domain		: '',
			URL			: '',
			body		: null,
			images		: null,
			applets		: null,
			links		: null,
			forms		: null,
			anchors		: null,
			cookie		: '',
			// Methods
			open				:
				function ()
				{
					return;
				},
			close				:
				function ()
				{
					return;
				},
			write				:
				function (text)
				{
					return;
				},
			writeln				:
				function (text)
				{
					return;
				},
			getElementsByName	:
				function (elementName)
				{
					return null;
				}
		};

// HTMLElement Interface
// http://www.w3.org/TR/DOM-Level-2-HTML/html.html#ID-011100101

var
	HTMLElement =
		{
			// Attributes
			id			: '',
			title		: '',
			lang		: '',
			dir			: '',
			className	: ''
		};

// Object Definitions
// http://www.w3.org/TR/DOM-Level-2-HTML/html.html#ID-798055546

var
	HTMLHtmlElement =
		{
			// Attributes
			version	: ''
		},
	HTMLHeadElement =
		{
			// Attributes
			profile	: ''
		},
	HTMLLinkElement =
		{
			// Attributes
			disabled	: false,
			charset		: '',
			href		: '',
			hreflang	: '',
			media		: '',
			rel			: '',
			rev			: '',
			target		: '',
			type		: ''
		},
	HTMLTitleElement =
		{
			// Attributes
			text	: ''
		},
	HTMLMetaElement =
		{
			// Attributes
			content		: '',
			httpEquiv	: '',
			name		: '',
			scheme		: ''
		},
	HTMLBaseElement =
		{
			// Attributes
			href	: '',
			target	: ''
		},
	HTMLIsIndexElement =
		{
			// Attributes
			form	: null,
			prompt	: ''
		},
	HTMLStyleElement =
		{
			// Attributes
			disabled	: false,
			media		: '',
			type		: ''
		},
	HTMLBodyElement =
		{
			// Attributes
			aLink		: '',
			background	: '',
			bgColor		: '',
			link		: '',
			text		: '',
			vLink		: ''
		},
	HTMLFormElement =
		{
			// Attributes
			elements		: null,
			length			: 0,
			name			: '',
			acceptCharset	: '',
			action			: '',
			enctype			: '',
			method			: '',
			target			: '',
			// Methods
			submit	:
				function ()
				{
					return;
				},
			reset	:
				function ()
				{
					return;
				}
		},
	HTMLSelectElement =
		{
			// Attributes
			type			: '',
			selectedIndex	: 0,
			value			: '',
			length			: 0,
			form			: null,
			options			: null,
			disabled		: false,
			multiple		: false,
			name			: '',
			size			: 0,
			tabIndex		: 0,
			// Methods
			add		:
				function (element, before)
				{
					return;
				},
			remove	:
				function (index)
				{
					return;
				},
			blur	:
				function ()
				{
					return;
				},
			focus	:
				function ()
				{
					return;
				}
		},
	HTMLOptGroupElement =
		{
			// Attributes
			disabled	: false,
			label		: ''
		},
	HTMLOptionElement =
		{
			// Attributes
			form			: null,
			defaultSelected	: false,
			text			: '',
			index			: 0,
			disabled		: false,
			label			: '',
			selected		: false,
			value			: ''
		},
	HTMLInputElement =
		{
			// Attributes
			defaultValue	: '',
			defaultChecked	: false,
			form			: null,
			accept			: '',
			accessKey		: '',
			align			: '',
			alt				: '',
			checked			: false,
			disabled		: false,
			maxLength		: 0,
			name			: '',
			readOnly		: false,
			size			: 0,
			src				: '',
			tabIndex		: 0,
			type			: '',
			useMap			: '',
			value			: '',
			// Methods
			blur	:
				function ()
				{
					return;
				},
			focus	:
				function ()
				{
					return;
				},
			select	:
				function ()
				{
					return;
				},
			click	:
				function ()
				{
					return;
				}
		},
	HTMLTextAreaElement =
		{
			// Attributes
			defaultValue	: '',
			form			: null,
			accessKey		: '',
			cols			: 0,
			disabled		: false,
			name			: '',
			readOnly		: false,
			rows			: 0,
			tabIndex		: 0,
			type			: '',
			value			: '',
			// Methods
			blur	:
				function ()
				{
					return;
				},
			focus	:
				function ()
				{
					return;
				},
			select	:
				function ()
				{
					return;
				}
		},
	HTMLButtonElement =
		{
			// Attributes
			form		: null,
			accessKey	: '',
			disabled	: false,
			name		: '',
			tabIndex	: 0,
			type		: '',
			value		: ''
		},
	HTMLLabelElement =
		{
			// Attributes
			form		: null,
			accessKey	: '',
			htmlFor		: ''
		},
	HTMLFieldSetElement =
		{
			// Attributes
			form	: null
		},
	HTMLLegendElement =
		{
			// Attributes
			form		: null,
			accessKey	: '',
			align		: ''
		},
	HTMLUListElement =
		{
			// Attributes
			compact	: false,
			type	: ''
		},
	HTMLOListElement =
		{
			// Attributes
			compact	: false,
			start	: 0,
			type	: ''
		},
	HTMLDListElement =
		{
			// Attributes
			compact	: false
		},
	HTMLDirectoryElement =
		{
			// Attributes
			compact	: false
		},
	HTMLMenuElement =
		{
			// Attributes
			compact	: false
		},
	HTMLLIElement =
		{
			// Attributes
			type	: '',
			value	: 0
		},
	HTMLDivElement =
		{
			// Attributes
			align	: ''
		},
	HTMLParagraphElement =
		{
			// Attributes
			align	: ''
		},
	HTMLHeadingElement =
		{
			// Attributes
			align	: ''
		},
	HTMLQuoteElement =
		{
			// Attributes
			cite	: ''
		},
	HTMLPreElement =
		{
			// Attributes
			width	: 0
		},
	HTMLBRElement =
		{
			// Attributes
			clear	: ''
		},
	HTMLBaseFontElement =
		{
			// Attributes
			color	: '',
			face	: '',
			size	: 0
		},
	HTMLFontElement =
		{
			// Attributes
			color	: '',
			face	: '',
			size	: ''
		},
	HTMLHRElement =
		{
			// Attributes
			align	: '',
			noShade	: false,
			size	: '',
			width	: ''
		},
	HTMLModElement =
		{
			// Attributes
			cite		: '',
			dateTime	: ''
		},
	HTMLAnchorElement =
		{
			// Attributes
			accessKey	: '',
			charset		: '',
			coords		: '',
			href		: '',
			hreflang	: '',
			name		: '',
			rel			: '',
			rev			: '',
			shape		: '',
			tabIndex	: 0,
			target		: '',
			type		: '',
			// Methods
			blur	:
				function ()
				{
					return;
				},
			focus	:
				function ()
				{
					return;
				}
		},
	HTMLImageElement =
		{
			// Attributes
			name		: '',
			align		: '',
			alt			: '',
			border		: '',
			height		: 0,
			hspace		: 0,
			isMap		: false,
			longDesc	: '',
			src			: '',
			useMap		: '',
			vspace		: 0,
			width		: 0
		},
	HTMLObjectElement =
		{
			// Attributes
			form		: null,
			code		: '',
			align		: '',
			archive		: '',
			border		: '',
			codeBase	: '',
			codeType	: '',
			data		: '',
			declare		: false,
			height		: '',
			hspace		: 0,
			name		: '',
			standby		: '',
			tabIndex	: 0,
			type		: '',
			useMap		: '',
			vspace		: 0,
			width		: ''
		},
	HTMLParamElement =
		{
			// Attributes
			name		: '',
			type		: '',
			value		: '',
			valueType	: ''
		},
	HTMLAppletElement =
		{
			// Attributes
			align		: '',
			alt			: '',
			archive		: '',
			code		: '',
			codeBase	: '',
			height		: '',
			hspace		: 0,
			name		: '',
			object		: '',
			vspace		: 0,
			width		: ''
		},
	HTMLMapElement =
		{
			// Attributes
			areas	: null,
			name	: ''
		},
	HTMLAreaElement =
		{
			// Attributes
			accessKey	: '',
			alt			: '',
			coords		: '',
			href		: '',
			noHref		: false,
			shape		: '',
			tabIndex	: 0,
			target		: ''
		},
	HTMLScriptElement =
		{
			// Attributes
			text		: '',
			htmlFor		: '',
			event		: '',
			charset		: '',
			defer		: false,
			src			: '',
			type		: ''
		},
	HTMLTableElement =
		{
			// Attributes
			caption		: null,
			tHead		: null,
			tFoot		: null,
			rows		: null,
			tBodies		: null,
			align		: '',
			bgColor		: '',
			border		: '',
			cellPadding	: '',
			cellSpacing	: '',
			frame		: '',
			rules		: '',
			summary		: '',
			width		: '',
			// Methods
			createTHead		:
				function ()
				{
					return null;
				},
			deleteTHead		:
				function ()
				{
					return;
				},
			createTFoot		:
				function ()
				{
					return null;
				},
			deleteTFoot		:
				function ()
				{
					return;
				},
			createCaption	:
				function ()
				{
					return null;
				},
			deleteCaption	:
				function ()
				{
					return;
				},
			insertRow		:
				function (index)
				{
					return null;
				},
			deleteRow		:
				function (index)
				{
					return;
				}
		},
	HTMLTableCaptionElement =
		{
			// Attributes
			align	: ''
		},
	HTMLTableColElement =
		{
			// Attributes
			align	: '',
			ch		: '',
			chOff	: '',
			span	: 0,
			vAlign	: '',
			width	: ''
		},
	HTMLTableSectionElement =
		{
			// Attributes
			align	: '',
			ch		: '',
			chOff	: '',
			vAlign	: '',
			rows	: null,
			// Methods
			insertRow	:
				function (index)
				{
					return null;
				},
			deleteRow	:
				function (index)
				{
					return null;
				}
		},
	HTMLTableRowElement =
		{
			// Attributes
			rowIndex		: 0,
			sectionRowIndex	: 0,
			cells			: null,
			align			: '',
			bgColor			: '',
			ch				: '',
			chOff			: '',
			vAlign			: '',
			// Methods
			insertCell	:
				function (index)
				{
					return null;
				},
			deleteCell	:
				function (index)
				{
					return;
				}
		},
	HTMLTableCellElement =
		{
			// Attributes
			cellIndex	: 0,
			abbr		: '',
			align		: '',
			axis		: '',
			bgColor		: '',
			ch			: '',
			chOff		: '',
			colSpan		: 0,
			headers		: '',
			height		: '',
			noWrap		: '',
			rowSpan		: 0,
			scope		: '',
			vAlign		: '',
			width		: ''
		},
	HTMLFrameSetElement =
		{
			// Attributes
			cols	: '',
			rows	: ''
		},
	HTMLFrameElement =
		{
			// Attributes
			frameBorder		: '',
			longDesc		: '',
			marginHeight	: '',
			marginWidth		: '',
			name			: '',
			noResize		: 0,
			scrolling		: '',
			src				: '',
			contentDocument	: ''
		},
	HTMLIFrameElement =
		{
			// Attributes
			align			: '',
			frameBorder		: '',
			height			: '',
			longDesc		: '',
			marginHeight	: '',
			marginWidth		: '',
			name			: '',
			scrolling		: '',
			src				: '',
			width			: '',
			contentDocument	: ''
		};

// ElementTraversal interface
// http://www.w3.org/TR/2008/REC-ElementTraversal-20081222/#interface-elementTraversal

var
	ElementTraversal =
		{
			// Attributes
			firstElementChild		: null,
			lastElementChild		: null,
			previousElementSibling	: null,
			nextElementSibling		: null,
			childElementCount		: 0
		};

// Basic interfaces
// http://www.w3.org/TR/DOM-Level-3-Events/events.html#Events-interface

var
	Event =
		{
			// Values
			// PhaseType
			CAPTURING_PHASE	: 1,
			AT_TARGET		: 2,
			BUBBLING_PHASE	: 3,
			// Events
			MOUSEDOWN	: 1,
			MOUSEUP		: 2,
			MOUSEOVER	: 4,
			MOUSEOUT	: 8,
			MOUSEMOVE	: 16,
			MOUSEDRAG	: 32,
			CLICK		: 64,
			DBLCLICK	: 128,
			KEYDOWN		: 256,
			KEYUP		: 512,
			KEYPRESS	: 1024,
			DRAGDROP	: 2048,
			FOCUS		: 4096,
			BLUR		: 8192,
			SELECT		: 16384,
			CHANGE		: 32768,
			RESET		: 65536,
			SUBMIT		: 131072,
			SCROLL		: 262144,
			LOAD		: 524288,
			UNLOAD		: 1048576,
			XFER_DONE	: 2097152,
			ABORT		: 4194304,
			ERROR		: 8388608,
			LOCATE		: 16777216,
			MOVE		: 33554432,
			RESIZE		: 67108864,
			FORWARD		: 134217728,
			HELP		: 268435456,
			BACK		: 536870912,
			// Unknown
			TEXT: void 0,
			// Key Masks
			ALT_MASK		: 1,
			CONTROL_MASK	: 2,
			SHIFT_MASK		: 4,
			META_MASK		: 8,
			// Attributes
			type				: '',
			target				: null,
			currentTarget		: null,
			eventPhase			: 0,
			bubbles				: false,
			cancelable			: false,
			timeStamp			: null,
			namespaceURI		: '',
			defaultPrevented	: false,
			// Methods
			stopPropagation				:
				function ()
				{
					return;
				},
			preventDefault				:
				function ()
				{
					return;
				},
			initEvent					:
				function (eventTypeArg, canBubbleArg, cancelableArg)
				{
					return;
				},
			stopImmediatePropagation	:
				function ()
				{
					return;
				},
			initEventNS					:
				function (namespaceURIArg, evenrTypeArg, canBubbleArg, cancelableArg)
				{
					return;
				},
			// Events
			DOMActivate					:
				function ()
				{
					return false;
				},
			DOMFocusIn					:
				function ()
				{
					return false;
				},
			DOMFocusOut					:
				function ()
				{
					return false;
				},
			focus						:
				function ()
				{
					return false;
				},
			blur						:
				function ()
				{
					return false;
				},
			textInput					:
				function ()
				{
					return false;
				},
			click						:
				function ()
				{
					return false;
				},
			dblclick					:
				function ()
				{
					return false;
				},
			mousedown					:
				function ()
				{
					return false;
				},
			mouseup						:
				function ()
				{
					return false;
				},
			mouseover					:
				function ()
				{
					return false;
				},
			mousemove					:
				function ()
				{
					return false;
				},
			mouseout					:
				function ()
				{
					return false;
				},
			keydown						:
				function ()
				{
					return false;
				},
			keyup						:
				function ()
				{
					return false;
				},
			mousemultiwheel				:
				function ()
				{
					return false;
				},
			mousewheel					:
				function ()
				{
					return false;
				},
			DOMSubtreeModified			:
				function ()
				{
					return false;
				},
			DOMNodeInserted				:
				function ()
				{
					return false;
				},
			DOMNodeRemoved				:
				function ()
				{
					return false;
				},
			DOMNodeRemovedFromDocument	:
				function ()
				{
					return false;
				},
			DOMNodeInsertedIntoDocument	:
				function ()
				{
					return false;
				},
			DOMAttrModified				:
				function ()
				{
					return false;
				},
			DOMCharacterDataModified	:
				function ()
				{
					return false;
				},
			DOMElementNameChanged		:
				function ()
				{
					return false;
				},
			DOMAttributeNameChanged		:
				function ()
				{
					return false;
				},
			load						:
				function ()
				{
					return false;
				},
			unload						:
				function ()
				{
					return false;
				},
			abort						:
				function ()
				{
					return false;
				},
			error						:
				function ()
				{
					return false;
				},
			select						:
				function ()
				{
					return false;
				},
			change						:
				function ()
				{
					return false;
				},
			submit						:
				function ()
				{
					return false;
				},
			reset						:
				function ()
				{
					return false;
				},
			resize						:
				function ()
				{
					return false;
				},
			scroll						:
				function ()
				{
					return false;
				}
		},
	CustomEvent =
		{
			// Attributes
			detail	: {},
			// Methods
			initCustomEventNS	:
				function (namespaceURIArg, typeArg, canBubbleArg, cancelableArg, detailArg)
				{
					return;
				}
		},
	EventTarget =
		{
			// Methods
			addEventListener		:
				function (type, listener, useCapture)
				{
					return;
				},
			removeEventListener		:
				function (type, listener, useCapture)
				{
					return;
				},
			dispatchEvent			:
				function (evt)
				{
					return false;
				},
			addEventListenerNS		:
				function (namespaceURI, type, listener, useCapture)
				{
					return;
				},
			removeEventListenerNS	:
				function (namespaceURI, type, listener, useCapture)
				{
					return;
				}
		},
	EventListener =
		{
			// Methods
			handleEvent	:
				function (evt)
				{
					return;
				}
		},
	EventException =
		{
			// Values
			// EventExceptionCode
			UNSPECIFIED_EVENT_TYPE_ERR	: 0,
			DISPATCH_REQUEST_ERR		: 1,
			// Attributes
			code	: 0
		},
	// This object is listed
	// separately in some places
	// and in DOMException in
	// others.  It is included
	// here for completeness.
	EventExceptionCode =
		{
			// Values
			// EventExceptionCode
			UNSPECIFIED_EVENT_TYPE_ERR	: 0,
			DISPATCH_REQUEST_ERR		: 1
		};

// Event Creation
// http://www.w3.org/TR/DOM-Level-3-Events/events.html#Events-document

var
	DocumentEvent =
		{
			// Methods
			createEvent	:
				function (eventType)
				{
					return null;
				},
			canDispatch	:
				function (namespaceURI, type)
				{
					return false;
				}
		};

// User Interface event types
// http://www.w3.org/TR/DOM-Level-3-Events/events.html#Events-eventgroupings-uievents

var
	UIEvent =
		{
			// Attributes
			view	: null,
			detail	: 0,
			// Methods
			initUIEvent		:
				function (typeArg, canBubbleArg, cancelableArg, viewArg, detailArg)
				{
					return;
				},
			initUIEventNS	:
				function (namespaceURIArg, typeArg, canBubbleArg, cancelableArg, viewArg, detailArg)
				{
					return;
				}
		};

// Text events types
// http://www.w3.org/TR/DOM-Level-3-Events/events.html#Events-TextEvents-Interfaces

var
	TextEvent =
		{
			// Attributes
			data	: '',
			// Methods
			initTextEvent	:
				function (typeArg, canBubbleArg, cancelableArg, viewArg, dataArg)
				{
					return;
				},
			initTextEventNS	:
				function (namespaceURIArg, typeArg, canBubbleArg, cancelableArg, viewArg, dataArg)
				{
					return;
				}
		};

// Keyboard event types
// http://www.w3.org/TR/DOM-Level-3-Events/events.html#Events-KeyboardEvents-Interfaces

var
	KeyboardEvent =
		{
			// Values
			// KeyLocationCode
			DOM_KEY_LOCATION_STANDARD	: 0x00,
			DOM_KEY_LOCATION_LEFT		: 0x01,
			DOM_KEY_LOCATION_RIGHT		: 0x02,
			DOM_KEY_LOCATION_NUMPAD		: 0x03,
			// Attributes
			keyIdentifier	: '',
			keyLocation		: 0,
			ctrlKey			: false,
			shiftKey		: false,
			altKey			: false,
			metaKey			: false,
			// Methods
			getModifierState	:
				function (keyIdentifierArg)
				{
					return false;
				},
			initKeyboardEvent	:
				function (typeArg, canBubbleArg, cancelableArg, viewArg, keyIdentifierArg, keyLocationArg, modifiersListArg)
				{
					return;
				},
			initKeyboardEventNS	:
				function (namespaceURIArg, typeArg, canBubbleArg, cancelableArg, viewArg, keyIdentifierArg, keyLocationArg, modifiersListArg)
				{
					return;
				}
		};

// Mouse event types
// http://www.w3.org/TR/DOM-Level-3-Events/events.html#Events-eventgroupings-mouseevents

var
	MouseEvent =
		{
			// Attributes
			screenX			: 0,
			screenY			: 0,
			clientX			: 0,
			clientY			: 0,
			ctrlKey			: false,
			shiftKey		: false,
			altKey			: false,
			metaKey			: false,
  			button			: 0,
			relatedTarget	: null,
			// Methods
			initUIEvent			:
				function (typeArg, canBubbleArg, cancelableArg, viewArg, detailArg, screenXArg, screenYArg, clientXArg, clientYArg, ctrlKeyArg, altKeyArg, shiftKeyArg, metaKeyArg, buttonArg, relatedTargetArg)
				{
					return;
				},
			getModifiersState	:
				function (keyIdentifierArg)
				{
					return false;
				},
			initUIEventNS		:
				function (namespaceURIArg, typeArg, canBubbleArg, cancelableArg, viewArg, detailArg, screenXArg, screenYArg, clientXArg, clientYArg, buttonArg, relatedTargetArg, modifiersListArg)
				{
					return;
				}
		};

// Mouse multi wheel event types
// http://www.w3.org/TR/DOM-Level-3-Events/events.html#Events-eventgroupings-mousemultiwheelevents

var
	MouseMultiWheelEvent =
		{
			// Attributes
			wheelDeltaX	: 0,
			wheelDeltaY	: 0,
			wheelDeltaZ	: 0,
			// Methods
			initMouseMultiWheelEventNS	:
				function (namespaceURIArg, typeArg, canBubbleArg, cancelableArg, viewArg, detailArg, screenXArg, screenYArg, clientXArg, clientYArg, buttonArg, relatedTargetArg, modifiersListArg, wheelDeltaXArg, wheelDeltaYArg, wheelDeltaZArg)
				{
					return;
				}
		};

// Mouse wheel event types
// http://www.w3.org/TR/DOM-Level-3-Events/events.html#Events-eventgroupings-mousewheelevents

var
	MouseWheelEvent =
		{
			// Attributes
			wheelDelta	: 0,
			// Methods
			initMouseWheelEventNS	:
				function (namespaceURIArg, typeArg, canBubbleArg, cancelableArg, viewArg, detailArg, screenXArg, screenYArg, clientXArg, clientYArg, buttonArg, relatedTargetArg, modifiersListArg, wheelDeltaArg)
				{
					return;
				}
		};

// Mutation event types
// http://www.w3.org/TR/DOM-Level-3-Events/events.html#Events-eventgroupings-mutationevents

var
	MutationEvent =
		{
			// Values
			// attrChangeType
			MODIFICATION	: 1,
			ADDITION		: 2,
			REMOVAL			: 3,
			// Attributes
			relatedNode	: null,
			prevValue	: '',
			newValue	: '',
			attrName	: '',
			attrChange	: 0,
			// Methods
			initMutationEvent	:
				function (typeArg, canBubbleArg, cancelableArg, relatedNodeArg, prevValueArg, newValueArg, attrNameArg, attrChangeArg)
				{
					return;
				},
			initMutationEventNS	:
				function (namespaceURIArg, typeArg, canBubbleArg, cancelableArg, relatedNodeArg, prevValueArg, newValueArg, attrNameArg, attrChangeArg)
				{
					return;
				}
		};

// Mutation name event types
// http://www.w3.org/TR/DOM-Level-3-Events/events.html#Events-eventgroupings-mutationnameevents

var
	MutationNameEvent =
		{
			// Attributes
			prevNamespaceURI	: '',
			prevNodeName		: '',
			// Methods
			initMutationNameEvent	:
				function (typeArg, canBubbleArg, cancelableArg, relatedNodeArg, prevNamespaceURIArg, prevNodeNameArg)
				{
					return;
				},
			initMutationNameEventNS	:
				function (namespaceURIArg, typeArg, canBubbleArg, cancelableArg, relatedNodeArg, prevNamespaceURIArg, prevNodeNameArg)
				{
					return;
				}
		};

// ================
//  Common Objects
// ================

var
	ActiveXObject =
		{
		},
	Image =
		{
			// Attributes
			name		: '',
			align		: '',
			alt			: '',
			border		: '',
			height		: 0,
			hspace		: 0,
			isMap		: false,
			longDesc	: '',
			src			: '',
			useMap		: '',
			vspace		: 0,
			width		: 0,
			complete	: false,
			id			: '',
			className	: '',
			title		: ''
		},
	XPCNativeWrapper =
		{
		},
	XPCSafeJSObjectWrapper =
		{
		},
	GeckoActiveXObject =
		{
		},
	QueryInterface =
		{
		},
	XMLHttpRequest =
		{
		},
	Components =
		{
		};

// ===================
//  Common Properties
// ===================

var
	applicationCache	= null,
	closed				= false,
	content				= null,
	_content			= null,
	controllers			= null,
	crypto				= null,
	defaultStatus		= '',
	dialogArguments		= null,
	directories			= null,
	document			= null,
	frameElement		= null,
	frames				= null,
	fullScreen			= false,
	globalStorage		= null,
	history				= null,
	innerHeight			= 0,
	innerWidth			= 0,
	length				= 0,
	location			= '',
	locationbar			= null,
	localStorage		= null,
	menubar				= null,
	// Causes conflicts
//	name				= '',
	navigator			= null,
	opener				= null,
	outerHeight			= 0,
	outerWidth			= 0,
	pageXOffset			= 0,
	pageYOffset			= 0,
	parent				= null,
	personalbar			= null,
	pkcs11				= null,
	returnValue			= null,
	screen				= null,
	screenX				= 0,
	screenY				= 0,
	scrollbars			= null,
	scrollMaxX			= 0,
	scrollMaxY			= 0,
	scrollX				= 0,
	scrollY				= 0,
	self				= null,
	sessionStorage		= null,
	sidebar				= null,
	status				= '',
	statusbar			= null,
	toolbar				= null,
	top					= null,
	window				= null;

// This is not strictly
// a global, but it's an
// undeclared local so
// gives warnings.
var
	arguments;

// ==================
//  Common Functions
// ==================

function alert(message)
{
	return;
}

function addEventListener(type, listener, useCapture)
{
	return;
}

function atob(encodedData)
{
	return '';
}

function back()
{
	return;
}

function blur()
{
	return;
}

function btoa(stringToEncode)
{
	return '';
}

function captureEvents(enebtType)
{
	return;
}

function clearInterval(intervalID)
{
	return;
}

function clearTimeout(timeoutID)
{
	return;
}

function close()
{
	return;
}

function confirm(message)
{
	return false;
}

function disableExternalCapture()
{
	return;
}

function dispatchEvent(event)
{
	return false;
}

function dump(message)
{
	return;
}

function enableExternalCapture()
{
	return;
}

function escape(regular)
{
	return '';
}

function find(aString, aCaseSensitive, aBackwards, aWrapAround, aWholeWord, aSearchInFrames, aShowDialog)
{
	return false;
}

function focus()
{
	return;
}

function forward()
{
	return;
}

function getAttention()
{
	return;
}

function getAttentionWithCycleCount(count)
{
	return;
}

function getComputedStyle(element, pseudoElt)
{
	return null;
}

function getSelection()
{
	return null;
}

function home()
{
	return;
}

function maximize()
{
	return;
}

function minimize()
{
	return;
}

function moveBy(deltaX, deltaY)
{
	return;
}

function moveTo(x, y)
{
	return;
}

function open(strUrl, strWindowName, strWindowFeatures)
{
	return null;
}

function openDialog(url, name, features)
{
	return null;
}

function postMessage(message, targetOrigin)
{
	return;
}

function print()
{
	return;
}

function prompt(text, value)
{
	return '';
}

function releaseEvents(eventType)
{
	return;
}

function removeEventListener(type, listener, useCapture)
{
	return;
}

function resizeBy(xDelta, yDelta)
{
	return;
}

function resizeTo(iWidth, iHeight)
{
	return;
}

function restore()
{
	return;
}

function routeEvent()
{
	return;
}

function scroll(xCoord, yCoord)
{
	return;
}

function scrollBy(x, y)
{
	return;
}

function scrollByLines(lines)
{
	return;
}

function scrollByPages(pages)
{
	return;
}

function scrollTo(xCoord, yCoord)
{
	return;
}

function setCursor(cursor)
{
	return;
}

function setInterval(func, delay)
{
	return 0;
}

function setResizable(set)
{
	return;
}

function setTimeout(func, delay)
{
	return 0;
}

function showModalDialog(uri)
{
	return null;
}

function sizeToContent()
{
	return;
}

function stop()
{
	return;
}

function unescape(escaped)
{
	return '';
}

function updateCommands(command)
{
	return;
}
