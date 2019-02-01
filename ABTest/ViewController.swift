//
//  ViewController.swift
//  ABTest
//
//  Created by Ricardo Ferreira on 20/12/2018.
//  Copyright © 2018 Ricardo Ferreira. All rights reserved.
//

import UIKit
import Alamofire
import OptimizelySDKiOS
import KiiSDK
import Firebase

class ViewController: UIViewController {
    
    let url = URL(string: "<URL>");
    let urlSession = URLSession(configuration: .default);
    var urlSessionTask: URLSessionDataTask?;
    var userId :String = ""

    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        
    }
    
    @IBAction func runExperiment(_ sender: UIButton) {
        performFirebaseExperiment()
    }
    
    private func performFirebaseExperiment() {
        InstanceID.instanceID().instanceID { (result, error) in
            if let error = error {
                print("Error fetching remote instance ID: \(error)")
            } else if let result = result {
                print("Remote instance ID token: \(result.token)")
            }
        }
    }
    
    private func performKiiExperiment() {
        let experiment : KiiExperiment
        do {
            experiment = try KiiExperiment.getSynchronous("78d7ecf4-0467-11e9-9fa5-22000a66c675")
        } catch _ as NSError {
            // Handle the error.
            return
        }
        
        
        let variationA: KiiVariation
        do {
            variationA = try experiment.appliedVariation()
        } catch {
            // Failed to apply a variation.
            // Get the error.code property for the cause of this error.
            // This sample code fallbacks to variation 'A' if it fails to randomly apply a variation.
            variationA = experiment.variation(byName: "A")!
        }
        
    }
    
    private func performOptimizelyExperiment() {
        let optimizelyClient :OPTLYClient? = nil
        
        let variation = optimizelyClient?.activate("HTTPLIBS", userId:userId)
        
        if let variation = variation {
            if variation.variationKey == "nsurlsession" {
                // execute code for nsurlsession
                urlSessionDownloadTask()
            } else if variation.variationKey == "alamofire" {
                // execute code for alamofire
                alamofireDownloadTask()
            }
        }
    }
    
    func urlSessionDownloadTask() {
        
        Analytics.logEvent("mainURLSessionGETTask", parameters: nil)
        
        urlSessionTask?.cancel();
        
        var urlRequest = URLRequest(url: url!,
                                    cachePolicy: .reloadIgnoringLocalAndRemoteCacheData,
                                    timeoutInterval: 10.0 * 1000)
        urlRequest.httpMethod = "GET"
        urlRequest.addValue("application/json", forHTTPHeaderField: "Accept")
        
        urlSessionTask = urlSession.dataTask(with: urlRequest) {
            data, response, error in defer { self.urlSessionTask = nil }
            if let error = error {
                print("DataTask error: %@", error.localizedDescription);
            } else if let _ = data,
                let response = response as? HTTPURLResponse,
                response.statusCode == 200 {
                let json = try? JSONSerialization.jsonObject(with: data!, options: [])
                print(json as Any)
            }
        }
        urlSessionTask?.resume()
    }
    
    
    func alamofireDownloadTask() {
        
                Alamofire.request(url!, method: .get, parameters: nil, encoding: JSONEncoding.default, headers: ["Accept":"application/json"])
                    .validate()
                    .responseJSON { response in
        
                        if response.result.isSuccess {
        //                    print(response.response!.statusCode)
                            print(response.result.value as Any)
                        } else {
                            print("DataTask error: ", response.response!.statusCode);
        
                        }
        
                }
    }
}

//let optimizelyClient :OPTLYClient? = nil
//
//let variation = optimizelyClient?.activate("HTTPLIBS", userId:userId)
//
//if let variation = variation {
//    if variation.variationKey == "nsurlsession" {
//        // execute code for nsurlsession
//        urlSessionDownloadTask()
//    } else if variation.variationKey == "alamofire" {
//        // execute code for alamofire
//        alamofireDownloadTask()
//    }
//}
